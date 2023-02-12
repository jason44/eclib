#include "ec_falloc.h"
#include <stdio.h>
static void *get_parent(void *parent);

void *ec_falloc(size_t size, void *parent) {
    struct EcFallocH *ret_h = (struct EcFallocH *)malloc(sizeof(EcFallocAlignH) + size);
    // if parent is null, parent->child is null
    if (parent != NULL) {
        struct EcFallocH *parent_h = EC_PTR_TO_H(parent);
        ret_h->parent = parent_h;
        ret_h->child = parent_h->child;
        parent_h->child = ret_h;
        if (ret_h->child != NULL)
            ret_h->child->parent = ret_h;
        return EC_H_TO_PTR(ret_h);
    } else {
        ret_h->parent = NULL;
        ret_h->child = NULL;
        return EC_H_TO_PTR(ret_h);
    }

}

void *ec_falloc_append(size_t size, void *ptr) {
    if (ptr == NULL) {
    void *ret = ec_falloc(size, ptr);
    return ret;
    }
    struct EcFallocH *ptr_h = NULL;
    ptr_h = EC_PTR_TO_H(ptr);
    while (ptr_h->child != NULL) {
        ptr_h = ptr_h->child;
    }
    void *ret = ec_falloc(size, EC_H_TO_PTR(ptr_h));
    return ret;
}

void ec_ffree(void *head) {
    struct EcFallocH *h = EC_PTR_TO_H(head);
    struct EcFallocH *temp = h;
    for (; temp != NULL; h = temp) {
        temp = h->child;
        free(h);
    }
}

void ec_ffree_all(void *ptr) {
    struct EcFallocH *h = EC_PTR_TO_H(ptr);
    while (h->parent != NULL) {
        printf("%p\n", h);
        h = h->parent;
    }
    puts("NOW");
    ec_ffree(EC_H_TO_PTR(h));
    puts("THEN");
}

void ec_ffree_one(void *ptr) {
    // remove str from list since we only want to free str
    struct EcFallocH *ptr_h = EC_PTR_TO_H(ptr);
    if (ptr_h->parent != NULL && ptr_h->child != NULL) {
        puts("both good");
        ptr_h->parent->child = ptr_h->child;
        ptr_h->child->parent = ptr_h->parent;
    } else if (ptr_h->parent != NULL && ptr_h->child == NULL) {
        puts("parent good");
        ptr_h->parent->child = NULL;
    } else if (ptr_h->parent == NULL && ptr_h->child != NULL) {
        puts("child good");
        ptr_h->child->parent = NULL;
    }

    puts("freed");
    free(ptr_h);
}

#ifdef _EC_FALLOC_IMPLICIT

    void *ec_falloc_implicit(size_t size);
    void ec_ffree_implicit();
#endif

