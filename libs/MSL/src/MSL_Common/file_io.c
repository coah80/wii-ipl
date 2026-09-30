#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum file_kinds { file_closed, file_disk, file_console, file_unavailable };
enum io_states { neutral, writing, reading, rereading };
enum io_modes { io_read = 1, io_write = 2, io_append = 4 };
extern int __flush_all(void);
extern int __flush_buffer(FILE*, size_t*);

#pragma exceptions on

int fclose(FILE* file)
{
    int flush_result, close_result;

    if (file == NULL)
        return -1;
    if (file->mode.file_kind == file_closed)
        return 0;

    flush_result = fflush(file);

    close_result = (*file->close_proc)(file->handle);

    file->mode.file_kind = file_closed;
    file->handle = 0;

    if (file->state.free_buffer)
        free((FILE*)file->buffer);
    return (flush_result || close_result) ? -1 : 0;
}

int fflush(FILE* file)
{
    int pos;

    if (file == NULL)
    {
        return __flush_all();
    }

    if (file->state.error != 0 || file->mode.file_kind == file_closed)
    {
        return -1;
    }

    if (file->mode.io_mode == io_read)
    {
        return 0;
    }

    if (file->state.io_state >= rereading)
    {
        file->state.io_state = reading;
    }

    if (file->state.io_state == reading)
    {
        file->buffer_len = 0;
    }

    if (file->state.io_state != writing)
    {
        file->state.io_state = neutral;
        return 0;
    }

    if (file->mode.file_kind != file_disk)
    {
        pos = 0;
    }
    else
    {
        pos = ftell(file);
    }

    if (__flush_buffer(file, NULL) != 0)
    {
        file->state.error = 1;
        file->buffer_len = 0;
        return -1;
    }

    file->state.io_state = neutral;
    file->pos = pos;
    file->buffer_len = 0;
    return 0;
}

int __msl_strnicmp(const char* str1, const char* str2, int n)
{
    int i;
    char c1, c2;

    for (i = 0; i < n; i++)
    {
        c1 = tolower(*str1++);
        c2 = tolower(*str2++);

        if (c1 < c2)
            return -1;

        if (c1 > c2)
            return 1;

        if (c1 == '\0')
            return 0;
    }

    return 0;
}

char* __msl_itoa(int value, char* str, unsigned int base)
{
    int negative;
    int length;
    char c;
    int start;
    int end;

    negative = 0;
    length = 0;

    if (value < 0)
    {
        value = -value;
        negative = 1;
    }

    do
    {
        int digit = value % base;

        if (digit > 9)
            str[length++] = digit + 0x37;
        else
            str[length++] = digit + 0x30;

        value /= base;
    } while (value != 0);

    if (negative != 0)
        str[length++] = '-';

    str[length++] = '\0';

    start = 0;
    end = strlen(str) - 1;

    while (start < end)
    {
        c = str[start];
        str[start++] = str[end];
        str[end--] = c;
    }

    return str;
}
