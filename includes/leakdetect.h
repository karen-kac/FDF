#ifndef LEAKDETECT_H
# define LEAKDETECT_H
# include <stdlib.h>

typedef struct
{
    void *p;
    size_t size;
    const char *file;
    unsigned int line;
} MEM_T;

void leak_detect_init(void);
void *leak_detelc_malloc(size_t, const char*, unsigned int);
void leak_detect_free(void*);
void leak_detect_check(void);

#endif
