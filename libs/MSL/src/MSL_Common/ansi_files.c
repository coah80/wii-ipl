#include <stdio.h>
#include <stdlib.h>

extern int __read_console(unsigned long, unsigned char*, size_t*, void*);
extern int __write_console(unsigned long, unsigned char*, size_t*, void*);
extern int __close_console(unsigned long);

#pragma exceptions on

unsigned char stdin_buff[0x100];
unsigned char stdout_buff[0x100];
unsigned char stderr_buff[0x100];

FILE __files[4] = {
    {
        0,
        {0, 1, 1, 2, 0, 0},
        {0, 0, 0, 0},
        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        stdin_buff,
        0x100,
        stdin_buff,
        0,
        0,
        0,
        0,
        0,
        __read_console,
        __write_console,
        __close_console,
        0,
        &__files[1],
    },
    {
        1,
        {0, 2, 1, 2, 0, 0},
        {0, 0, 0, 0},
        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        stdout_buff,
        0x100,
        stdout_buff,
        0,
        0,
        0,
        0,
        0,
        __read_console,
        __write_console,
        __close_console,
        0,
        &__files[2],
    },
    {
        2,
        {0, 2, 0, 2, 0, 0},
        {0, 0, 0, 0},
        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        stderr_buff,
        0x100,
        stderr_buff,
        0,
        0,
        0,
        0,
        0,
        __read_console,
        __write_console,
        __close_console,
        0,
        &__files[3],
    },
    {0},
};

void __close_all(void) {
    FILE* file;
    FILE* current;

    for (file = __files; file != 0;) {
        if (file->mode.file_kind != 0) {
            fclose(file);
        }

        current = file;
        file = file->next_file;
        if (current->is_dyn_alloc != 0) {
            free(current);
        } else {
            current->mode.file_kind = 3;
            if (file != 0 && file->is_dyn_alloc != 0) {
                current->next_file = 0;
            }
        }
    }
}

int __flush_all(void) {
    int result = 0;
    FILE* file;

    for (file = __files; file != 0; file = file->next_file) {
        if (file->mode.file_kind != 0 && fflush(file) != 0) {
            result = -1;
        }
    }

    return result;
}
