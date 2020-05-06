#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

void *OPT_malloc(size_t size);
void *OPT_calloc(size_t count, size_t size);
void *OPT_realloc(void *ptr, size_t size);
void OPT_free(void *ptr);
size_t OPT_allocatedMemory();

#endif // UTIL_H