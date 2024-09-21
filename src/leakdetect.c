#include <stdio.h>
#include <stdlib.h>
#include "leakdetect.h"

#define N 500

MEM_T mi[N];

void leak_detect_init()
{
    for (int i = 0; i < N; i++)
    {
        mi[i].p = NULL;
        mi[i].size = 0;
        mi[i].file = NULL;
        mi[i].line = 0;
    }
}

void *leak_detelc_malloc(size_t size, const char *file, unsigned int line)
{
    void *p;

    if (!(p = malloc(size)))
        return NULL;
    for (int i = 0; i < N; i++)
    {
        if (mi[i].p == NULL)
        {
            mi[i].p = p;
            mi[i].size = size;
            mi[i].file = file;
            mi[i].line = line;
            break;
        }
    }
    return p;
}

void leak_detect_free(void *p)
{
    for (int i = 0; i < N; i++)
    {
        if (mi[i].p == p)
        {
            mi[i].p = NULL;
            mi[i].size = 0;
            mi[i].file = NULL;
            mi[i].line = 0;
            break;
        }
    }
    free(p);
    p = NULL;
}

void leak_detect_check()
{
    for (int i = 0; i < N; i++)
    {
        if (mi[i].p != NULL)
        {
            printf("=== memory leak ===\n");
            printf(" adress : %p\n", mi[i].p);
            printf(" size   : %u\n", (unsigned int)mi[i].size);
            printf(" where  : %s:%u\n", mi[i].file, mi[i].line);
            printf("===================\n\n");
        }
    }
}
