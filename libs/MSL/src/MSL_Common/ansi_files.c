#include <stdio.h>
#include <stdlib.h>

int __read_console(unsigned long, unsigned char*, size_t*, void*);
int __write_console(unsigned long, unsigned char*, size_t*, void*);
int __close_console(unsigned long);

unsigned char stderr_buff[0x100];
unsigned char stdout_buff[0x100];
unsigned char stdin_buff[0x100];

void __close_all(void) {
    FILE* pFile = __files;

    while (pFile != 0) {
        if (pFile->mode.file_kind != 0) {
            fclose(pFile);
        }

        {
            FILE* pCurrent = pFile;
            pFile = pCurrent->next_file;

            if (pCurrent->is_dyn_alloc != 0) {
                free(pCurrent);
            } else {
                pCurrent->mode.file_kind = 3;

                if (pFile != 0 && pFile->is_dyn_alloc != 0) {
                    pCurrent->next_file = 0;
                }
            }
        }
    }
}

int __flush_all(void) {
    int result = 0;
    FILE* pFile = __files;

    while (pFile != 0) {
        if (pFile->mode.file_kind != 0) {
            if (fflush(pFile) != 0) {
                result = -1;
            }
        }

        pFile = pFile->next_file;
    }

    return result;
}

FILE __files[4] = {
    {0, {0, 1, 1, 2, 0, 0}, {0, 0, 0, 0}, 0, 0, 0, {0}, {0}, 0, stdin_buff, 0x100, stdin_buff, 0, 0, 0, 0, 0, __read_console, __write_console, __close_console, 0, &__files[1]},
    {1, {0, 2, 1, 2, 0, 0}, {0, 0, 0, 0}, 0, 0, 0, {0}, {0}, 0, stdout_buff, 0x100, stdout_buff, 0, 0, 0, 0, 0, __read_console, __write_console, __close_console, 0, &__files[2]},
    {2, {0, 2, 0, 2, 0, 0}, {0, 0, 0, 0}, 0, 0, 0, {0}, {0}, 0, stderr_buff, 0x100, stderr_buff, 0, 0, 0, 0, 0, __read_console, __write_console, __close_console, 0, &__files[3]},
    {0}
};
