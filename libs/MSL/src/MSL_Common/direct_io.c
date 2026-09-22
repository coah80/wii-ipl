#include <internal/file_struct.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>

enum file_kinds {
    file_closed,
    file_disk,
    file_console,
    file_unavailable
};

enum io_states {
    neutral,
    writing,
    reading,
    rereading
};

enum io_modes {
    io_read = 1,
    io_write = 2,
    io_append = 4
};

enum buffer_modes {
    buffer_none,
    buffer_full,
    buffer_line
};

void __prep_buffer(FILE* file);
int __flush_buffer(FILE* file, size_t* pos);
void __stdio_atexit(void);
int _fseek(FILE* file, long offset, int whence);
void* __memrchr(const void* ptr, int ch, size_t count);

size_t __fwrite(const void* ptr, size_t memb_size, size_t num_memb, FILE* file) {
    unsigned char* cur_ptr;
    size_t num_bytes, rem_bytes, bytes_written;
    int res, buff;

    if (fwide(file, 0) == 0) {
        fwide(file, -1);
    }

    rem_bytes = memb_size * num_memb;

    if (rem_bytes == 0 || file->state.error || file->mode.file_kind == file_closed) {
        return 0;
    }

    if (file->mode.file_kind == file_console) {
        __stdio_atexit();
    }

    buff = !file->mode.binary_io || file->mode.buffer_mode == buffer_line || file->mode.buffer_mode == buffer_full;

    if (file->state.io_state == neutral && file->mode.io_mode & io_write) {
        if (file->mode.io_mode & io_append) {
            if (_fseek(file, 0, 2)) {
                return 0;
            }
        }

        file->state.io_state = writing;
        __prep_buffer(file);
    }

    if (file->state.io_state != writing) {
        file->state.error = 1;
        file->buffer_len = 0;
        return 0;
    }

    cur_ptr = (unsigned char*)ptr;
    bytes_written = 0;

    if (rem_bytes && (file->buffer_ptr != file->buffer || buff)) {
        file->buffer_len = file->buffer_size - (file->buffer_ptr - file->buffer);

        do {
            unsigned char* nw = NULL;
            num_bytes = file->buffer_len;

            if (num_bytes > rem_bytes) {
                num_bytes = rem_bytes;
            }

            if (file->mode.buffer_mode == buffer_full && num_bytes) {
                if ((nw = (unsigned char*)__memrchr(cur_ptr, '\n', num_bytes)) != NULL) {
                    num_bytes = nw + 1 - cur_ptr;
                }
            }

            if (num_bytes != 0) {
                memcpy(file->buffer_ptr, cur_ptr, num_bytes);
                cur_ptr += num_bytes;
                rem_bytes -= num_bytes;
                file->buffer_ptr += num_bytes;
                file->buffer_len -= num_bytes;
            }

            if (file->buffer_len == 0 || nw != 0 || file->mode.buffer_mode == buffer_none) {
                res = __flush_buffer(file, 0);

                if (res != 0) {
                    file->state.error = 1;
                    file->buffer_len = 0;
                    rem_bytes = 0;
                    break;
                }
            }

            bytes_written += num_bytes;

        } while (rem_bytes && buff);
    }

    if (rem_bytes && buff == 0) {
        unsigned char* save_buf = file->buffer;
        size_t save_size = file->buffer_size;

        file->buffer = cur_ptr;
        file->buffer_size = rem_bytes;
        file->buffer_ptr = cur_ptr + rem_bytes;

        if (__flush_buffer(file, &num_bytes) != 0) {
            file->state.error = 1;
            file->buffer_len = 0;
        } else {
            bytes_written += num_bytes;
        }

        file->buffer = save_buf;
        file->buffer_size = save_size;
        __prep_buffer(file);
        file->buffer_len = 0;
    }

    if (file->mode.buffer_mode != buffer_line) {
        file->buffer_len = 0;
    }

    return bytes_written / memb_size;
}
