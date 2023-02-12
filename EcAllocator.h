#include <stdlib.h>
#include <stdio.h>

#include "ec_base.h"

#ifndef EC_ALLOCATOR_
#define EC_ALLOCATOR_

typedef enum EcAllocatorInitFlags {
    EC_ALLOC_FLAGS_NONE,
    EC_ALLOC_RESIZE_FULL = 1 << 1,
    EC_ALLOC_ZEROES      = 1 << 2
} EcAllocatorFlags;

struct EcAllocator {
    void *buf, *top;
    // needed for padding
    size_t prev_alloc;
    size_t size;
    size_t cap;
};

#define ec_alloc_type(type, alloc) ec_alloc_size(sizeof(type), alignof(type), alloc)
#define ec_alloc_ntype(type, n, alloc) ec_alloc_size(sizeof(type)*n, alignof(type), alloc)

EcRes ec_allocator_init(size_t size, EcAllocatorFlags flags,
                        struct EcAllocator *alloc);
inline void ec_allocator_free(struct EcAllocator *alloc) {
    free(alloc->buf);
    alloc->buf = NULL;
}
void *ec_alloc_size(size_t size, size_t t_align, struct EcAllocator *alloc);

#endif
