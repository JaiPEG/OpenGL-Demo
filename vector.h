#ifndef VECTOR_H221
#define VECTOR_H221

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

typedef struct
{
    void* base;
    unsigned int size;
    unsigned int alloc;
} Vector;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void vector_init(Vector* vector, unsigned int size_item);
void vector_push(Vector* vector, const void* item, unsigned int size_item);
void vector_pushBulk(Vector* vector, const void* items, unsigned int size_item, unsigned int count);
void vector_pop(Vector* vector, void* item_ret, unsigned int size_item);
void vector_popBulk(Vector* vector, void* items_ret, unsigned int size_item, unsigned int count);
void vector_destroy(Vector* vector, BOOL freePointers);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // VECTOR_H221