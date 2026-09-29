#include <private/nhttp.h>

#include <stdio.h>
s32 NHTTPi_compareToken(const char* lhs, const char* rhs);
void* NHTTPi_alloc(u32 size, int align);
void NHTTPi_SetError(NHTTPBgnEndInfo* info, NHTTPErr error);

static BOOL addHdrList(NHTTPHeader** list, NHTTPBgnEndInfo* info, char* name,
    char* value)
{
    BOOL found = FALSE;
    NHTTPHeader* header = *list;

    if (header != NULL)
    {
        if (NHTTPi_compareToken(name, header->name) != 0)
        {
            header = header->prev;
            while (header != *list)
            {
                if (NHTTPi_compareToken(name, header->name) == 0)
                {
                    found = TRUE;
                    break;
                }
                header = header->prev;
            }
        }
        else
        {
            found = TRUE;
        }
    }

    if (found)
    {
        header->value = value;
    }
    else
    {
        header = NHTTPi_alloc(sizeof(NHTTPHeader), 4);
        if (header == NULL)
        {
            printf("failed to allocate memory\n");
            NHTTPi_SetError(info, NHTTP_ERROR_ALLOC);
            return FALSE;
        }

        header->name = name;
        header->value = value;
        header->length = 0;
        header->_unk14 = 0;

        if (*list != NULL)
        {
            header->next = (*list)->next;
            header->prev = *list;
            (*list)->next->prev = header;
            (*list)->next = header;
        }
        else
        {
            header->prev = header;
            header->next = header;
            *list = header;
        }
    }

    return TRUE;
}

NHTTPHeader* NHTTPi_getHdrFromList(NHTTPHeader** list)
{
    NHTTPHeader* header = *list;

    if (header != NULL)
    {
        if (header != header->next)
        {
            header->next->prev = header->prev;
            header->prev->next = header->next;
            *list = header->prev;
        }
        else
        {
            *list = NULL;
        }
    }

    return header;
}

BOOL NHTTP_AddHeaderField(NHTTPRequestInfo* request, NHTTPBgnEndInfo* info,
    char* name, char* value)
{
    if (request->state != 0)
    {
        return FALSE;
    }
    return addHdrList(&request->headers, info, name, value);
}

