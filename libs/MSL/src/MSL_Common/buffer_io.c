#include <stdio.h>
#include <stdlib.h>

void __prep_buffer(FILE* pFile) {
    pFile->buffer_ptr = pFile->buffer;
    pFile->buffer_len = pFile->buffer_size;
    pFile->buffer_len -= pFile->pos & pFile->buffer_alignment;
    pFile->buffer_pos = pFile->pos;
}

int __flush_buffer(FILE* pFile, size_t* pFlushed) {
    size_t len;
    int res;

    len = pFile->buffer_ptr - pFile->buffer;

    if (len != 0) {
        pFile->buffer_len = len;

        res = (*pFile->write_proc)(pFile->handle, pFile->buffer, (size_t*)&pFile->buffer_len, pFile->ref);

        if (pFlushed != 0) {
            *pFlushed = pFile->buffer_len;
        }

        if (res != 0) {
            return res;
        }

        pFile->pos += pFile->buffer_len;
    }

    __prep_buffer(pFile);

    return 0;
}

int setvbuf(FILE* pFile, char* buffer, int mode, size_t size) {
    int file_kind = pFile->mode.file_kind;

    if (mode == _IONBF) {
        fflush(pFile);
    }

    if (pFile->state.io_state != 0 || file_kind == 0) {
        return -1;
    }

    if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF) {
        return -1;
    }

    if (pFile->buffer != 0 && pFile->state.free_buffer != 0) {
        free(pFile->buffer);
    }

    pFile->mode.buffer_mode = mode;
    pFile->state.free_buffer = 0;
    pFile->buffer = &pFile->char_buf;
    pFile->buffer_ptr = pFile->buffer;
    pFile->buffer_size = 1;
    pFile->buffer_len = 0;
    pFile->buffer_alignment = 0;

    if (mode == _IONBF || size < 1) {
        *pFile->buffer_ptr = 0;
        return 0;
    }

    if (buffer == 0) {
        buffer = malloc(size);
        if (buffer == 0) {
            return -1;
        }
        pFile->state.free_buffer = 1;
    }

    pFile->buffer = (unsigned char*)buffer;
    pFile->buffer_ptr = (unsigned char*)buffer;
    pFile->buffer_size = size;
    pFile->buffer_alignment = 0;
    return 0;
}
