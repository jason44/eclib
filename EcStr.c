#include "EcStr.h"
#include "ec_falloc.h"
#include <string.h>

/*void ec_strbufcat(struct EcStrBuf *dst, const struct EcStrBuf src) {
    const size_t newsize = dst->alloc.size + src.alloc.size;
    char newstr = ec_alloc_ntype(char, newsize + 1)
    memcpy(newstr, dst->p, dst->size);
    memcpy(&newstr[dst->size], src.p, src.size);
    newstr[newsize] = '\0';
    dst->p = newstr;
    dst->size = newsize;
    printf("%s\n%s\n", newstr, dst->p);
}*/

static char *rplce_chars(char *p, size_t size);

struct EcStr ec_strnew(size_t len, struct EcStr parent) {
    return ec_strnew_p(len, parent.p);
}

struct EcStr ec_strnew_p(size_t len, void *parent) {

    struct EcStr ret = (struct EcStr) {
        .size = len,
        .p = ec_falloc(sizeof(char) * (len + 1), parent)
    };

    return ret;
}

struct EcStr ec_strnew_literal(const char *literal, struct EcStr parent) {
    return ec_strnew_literal_p(literal, parent.p);
}

struct EcStr ec_strnew_literal_p(const char *literal, void *parent) {
    size_t len = strlen(literal);
    printf("strlen: %lu\n", len);
    struct EcStr ret = {
        .size = len,
        .p = ec_falloc(sizeof(char) * (len + 1), parent)
    };
    memcpy(ret.p, literal, (len + 1));
    return  ret;
}

// FIX: freeing stack memory when using ec_strnew_literal
void ec_strcpy(struct EcStr *dst, const struct EcStr src) {
    if (dst->size < src.size) {
    char *newbuf = rplce_chars(dst->p, sizeof(char) * (src.size + 1));
    // + 1 for '\0'
    memcpy(newbuf, src.p, src.size + 1);
    dst->p = newbuf;
    } else {
        memcpy(dst->p, src.p, src.size + 1);
    }
    dst->size = src.size;
}

// FIX: freeing stack memory when using ec_strnew_literal
void ec_strncpy(struct EcStr *dst, const struct EcStr src, size_t n) {
    if (dst->size < n + 1) {
    char *newbuf = rplce_chars(dst->p, sizeof(char) * (n + 1));
    // + 1 for '\0'
    memcpy(newbuf, src.p, n);
    newbuf[n] = '\0';
    dst->p = newbuf;
    } else {
        memcpy(dst->p, src.p, n);
        dst->p[n] = '\0';
    }
    dst->size = n;
}

void ec_strcat(struct EcStr *dst, const struct EcStr src) {
    size_t newsize = dst->size + src.size;
    printf("newsize: %lu\n", newsize);
    char *newbuf = rplce_chars(dst->p, newsize + 1);
    puts("LALALALLALALALALLAL");
    memcpy(newbuf, dst->p, dst->size);
    // + 1 for '\0'
    memcpy(newbuf + dst->size, src.p, src.size + 1);
    newbuf[newsize] = '\0';
    dst->p = newbuf;
    dst->size = newsize;
}

void ec_strfree(struct EcStr str) {
    ec_ffree(str.p);
}

void ec_strfree_all(struct EcStr str) {
   ec_ffree_all(str.p);
}

void ec_strfree_one(struct EcStr str) {
    ec_ffree_one(str.p);
}

/* FIX: when p -> parent is being used in ec_strcat, segfault */
static char *rplce_chars(char *p, size_t size) {
    struct EcFallocH *p_h = EC_PTR_TO_H(p);
    char *ret = (char *)ec_falloc(size, EC_H_TO_PTR(p_h->parent));
    ec_ffree_one(p);
    return ret;
}
