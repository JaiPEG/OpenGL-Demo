#include "util.h"

static size_t g_allocatedMemory = 0;

void *OPT_malloc(size_t size)
{
    void *ret = malloc(size);
    
    if (ret)
        g_allocatedMemory += size;
    
    return ret;
}

void *OPT_calloc(size_t count, size_t size)
{
    void *ret = calloc(count, size);
    
    if (ret)
        g_allocatedMemory += count * size;
    
    return ret;
}

void *OPT_realloc(void *ptr, size_t size)
{
    void *ret = realloc(ptr, size);
    
    if (ret)
        g_allocatedMemory += size;
    
    return ret;
}

void OPT_free(void *ptr)
{
    // TODO: g_allocatedMemory -= 
    free(ptr);
}

size_t OPT_allocatedMemory()
{
    return g_allocatedMemory;
}