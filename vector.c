#include "vector.h"

#include <stdlib.h>
#include <memory.h>
#include "bits.h"

#define PHI 1.61803398875

void vector_init(Vector* vector, unsigned int size_item)
{
    unsigned int alloc;
    
    if (vector)
    {
        vector->base = NULL;
        vector->size = 0;
        vector->alloc = 0;

        alloc = size_item << 2;

        if (vector->base = malloc(alloc))
        {
            vector->alloc = alloc;
        }
    }
}

void vector_push(Vector* vector, const void* item, unsigned int size_item)
{
    void* newBase;
    unsigned int newAlloc;
    
    if (vector && item && size_item)
    {
        // if need resizing
        if (vector->size + size_item > vector->alloc)
        {
            newAlloc = vector->alloc << 1;
            
            // if successfully resized
            if (newBase = realloc(vector->base, newAlloc))
            {
                vector->base = newBase;
                vector->alloc = newAlloc;
            }
            else
            {
                return;
            }
        }

        memcpy((char*)vector->base + vector->size, item, size_item);

        vector->size += size_item;
    }
}

void vector_pushBulk(Vector* vector, const void* items, unsigned int size_item, unsigned int count)
{
    void* newBase;
    unsigned int newAlloc;
    unsigned int size_items;
    
    if (vector && items && size_item)
    {
        size_items = size_item * count;
        
        // if need resizing
        if (vector->size + size_items > vector->alloc)
        {
            // round-up new alloc size to 1 power of 2 above new size
            newAlloc = 1U << (log2(vector->size + size_items) + 1U);
            
            // if successfully resized
            if (newBase = realloc(vector->base, newAlloc))
            {
                vector->base = newBase;
                vector->alloc = newAlloc;

                memcpy((char*)vector->base + vector->size, items, size_items);

                vector->size += size_items;
            }
        }
    }
}

void vector_pop(Vector* vector, void* item_ret, unsigned int size_item)
{
    void* newBase;
    unsigned int newAlloc;
    
    if (vector && item_ret && size_item)
    {
        // if anything to be popped
        if (vector->size > size_item)
        {
            memcpy(item_ret, (char*)vector->base + vector->size - size_item, size_item);

            vector->size -= size_item;

            // if worth resizing
            if (vector->size < vector->alloc >> 2)
            {
                newAlloc = vector->alloc >> 1;
                
                // if successfully resized
                if (newBase = realloc(vector->base, newAlloc))
                {
                    vector->base = newBase;
                    vector->alloc = newAlloc;
                }
            }
        }
    }
}

void vector_popBulk(Vector* vector, void* items_ret, unsigned int size_item, unsigned int count)
{
    void* newBase;
    unsigned int newAlloc;
    unsigned int size_items;
    
    if (vector && items_ret && size_item)
    {
        size_items = size_item * count;
        
        // if anything to be popped
        if (vector->size > size_items)
        {
            memcpy(items_ret, (char*)vector->base + vector->size - size_items, size_items);

            vector->size -= size_items;

            // if worth resizing
            if (vector->size < vector->alloc >> 2)
            {
                // round-up new alloc size two powers of two above vector->size
                newAlloc = 1U << (log2(vector->size) + 2U);
                
                // if successfully resized
                if (newBase = realloc(vector->base, newAlloc))
                {
                    vector->base = newBase;
                    vector->alloc = newAlloc;
                }
            }
        }
    }
}

void vector_destroy(Vector* vector, BOOL freePointers)
{
    unsigned int i;

    if (vector)
    {
        if (freePointers)
        {
            for (i = 0; i < vector->size / sizeof(void*); ++i)
            {
                free(((void**)vector->base) + i);
            }
        }

        free(vector->base);
        vector->base = NULL;
        vector->size = 0;
        vector->alloc = 0;
    }
}

/* NOTES
 * 
 * Consider using phi as vector scale factor.
 *
 * Use phi because it equals the ratio of one fibonnaci number to one previous.
 * I.e.: repeated multiplication by phi gives # equal to all previous additions,
 * i.e.: all previously allocated (and freed) memory blocks.
 *
 * Good for resizing into previously freed memory blocks.
 * Keeps memory allocations local.
*/