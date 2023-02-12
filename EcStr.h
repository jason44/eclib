#include "EcAllocator.h"
#include "ec_base.h"

#ifndef EC_STR_
#define EC_STR_

// TODO: strcpy; strcat; strdup; etc without the usage of strlen don't forget to add \0
// Before that, write a tree / list allocator where each allocation keeps
// a reference of the parent & child. for allocating EcStr, keep references in a stack
// so we can implicitly assign child & parent.

// priv
struct _StrBufAlloc{
    void *buf, *top;
    // needed for padding
    int size;
    int cap;
};
//

struct EcStr {
    char *p;
    int   size;
};

struct EcStrBuf {
    struct _StrBufAlloc alloc;
    char                 *p;
};

#define ec_strdup
//void ec_strbufcat(struct EcStrBuf *dst, const struct EcStrBuf src);

struct EcStr ec_strnew(size_t len, struct EcStr parent);
struct EcStr ec_strnew_p(size_t len, void *arent);
struct EcStr ec_strnew_literal(const char *literal, struct EcStr parent);
struct EcStr ec_strnew_literal_p(const char *literal, void *parent);
void ec_strcpy(struct EcStr *dst, const struct EcStr src);
void ec_strncpy(struct EcStr *dst, const struct EcStr src, size_t n);
void ec_strcat(struct EcStr *dst, const struct EcStr src);
void ec_strfree(struct EcStr str);
void ec_strfree_all(struct EcStr str);
void ec_strfree_one(struct EcStr str);


#endif
