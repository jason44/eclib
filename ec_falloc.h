#include <stdlib.h>

#ifndef _EC_FALLOC_
#define _EC_FALLOC_

#define MALLOC_ALIGNMENT 16

struct EcFallocH {
   struct EcFallocH *parent;
   struct EcFallocH *child;
};

typedef union EcFallocAlignH {
    char padding[((sizeof(struct EcFallocH) + MALLOC_ALIGNMENT - 1) & ~(MALLOC_ALIGNMENT - 1))];
} EcFallocAlignH;

#define EC_H_TO_PTR(header) (void *)(((EcFallocAlignH *)header) + 1)
#define EC_PTR_TO_H(ptr) (struct EcFallocH *)(((EcFallocAlignH *)ptr) - 1)
#define ec_falloc_type(type, parent) ec_falloc(sizeof(type), parent)
#define ec_falloc_ntype(type, n, parent) ec_falloc(sizeof(type) * n, parent)

// if parent has a child, insert betwee the two
// pass NULL if it is the first allocation
void *ec_falloc(size_t size, void *parent);
// add to the end of a family by passing arbitrary family member
void *ec_falloc_append(size_t size, void *ptr);
// frees head and all preceeding members
void ec_ffree(void *head);
// frees whole family
void ec_ffree_all(void *ptr);
// removes and frees ptr from list
void ec_ffree_one(void *ptr);

#ifdef _EC_FALLOC_IMPLICIT
    extern struct EcFallocH *global_family = NULL;
    extern struct EcFallocH *global_family_iter = NULL;

    void *ec_falloc_implicit(size_t size);
    void ec_ffree_implicit();
#endif

#endif
