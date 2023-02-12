#include "EcAllocator.h"

EcRes ec_allocator_init(size_t size, EcAllocatorFlags flags,
                        struct EcAllocator *alloc) {
    void *buf;
    if ((flags & EC_ALLOC_ZEROES) == EC_ALLOC_ZEROES)
        buf = calloc(size, sizeof(char));
    else
        buf = malloc(size);
    *alloc = (struct EcAllocator) {
        .buf = buf,
        .top = buf,
        .cap = size
    };
    if (alloc->buf == NULL)
        return EC_MALLOC_FAIL;
    if(alloc->top != alloc->buf)
        puts("compiler error?");

    return EC_SUCCESS;
}

void *ec_alloc_size(size_t size, size_t t_align, struct EcAllocator *alloc) {
    if ((alloc->cap - alloc->size) < size) {
        puts("allocator is full");
        return NULL;
    }
    size_t padding = ((alloc->prev_alloc + t_align - 1) & ~(t_align - 1)) - alloc->prev_alloc;
    const size_t total_size = size + padding;
    alloc->top = (void *)((char *)alloc->top + total_size);
    alloc->size += total_size;
    alloc->prev_alloc = size;
#ifdef  _EC_DEBUG
    printf("padding: %lu\n", padding);
#endif
    return alloc->top;
}
