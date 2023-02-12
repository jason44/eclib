#include "EcAllocator.h"
#include "EcStr.h"
#include "ec_falloc.h"
#include <stdio.h>
#include <stdint.h>

int main() {
/*    uint32_t *a = ec_falloc(sizeof(uint32_t), NULL);
    uint64_t *b = ec_falloc(sizeof(uint64_t), a);
    uint64_t *c = ec_falloc_append(sizeof(uint64_t), a);

    ec_ffree_all(b);

    char *hll = malloc(sizeof(char) * 5);
    printf("%s\n", hll);
    printf("[4]: %c [5]: %c [6]: %c\n", hll[4], hll[5], hll[6]);
    free(hll);

    char ty[5] = "HELLO";
    printf("%s\n", ty);
    // '\0' is placed after the last char
    printf("%c\n", ty[5]);
    // past the '\0' is just junk memory
    printf("%c\n", ty[6]);
    // sizeof doesn't account for '\0'
    printf("%lu\n", sizeof(ty));

    // buffer should have one more byte than scanf limit so '\0' doesn't overflow
    char scan_buf[6];
    scanf("%5s", scan_buf);
    printf("result: %s\n", scan_buf);
    // scanf inserts '\0' as last byte
    // '\0' doesn't count towards the char limit specified
    printf("%c\n", scan_buf[5]);
    // anything past '\0' would either be empty or junk memory
    printf("%c\n", scan_buf[6]);

 /*   uint32_t *a = malloc(sizeof(uint32_t));
    uint64_t *b = malloc(sizeof(uint64_t));

    free(a);
    free(b); */

    struct EcStr b = ec_strnew_p(5, NULL);
    struct EcStr a = ec_strnew(5, b);
    struct EcStr c = ec_strnew(6, a);
    struct EcStr t = ec_strnew(3, b);
    struct EcStr l = ec_strnew_literal("HELLO", c);
    struct EcStr m = ec_strnew_literal("Fuck", l);
    struct EcStr k = ec_strnew_literal("RONDO LOL", b);
    ec_strcat(&m, l);
    ec_strcpy(&l, k);

    printf("%s\n", m.p);
    printf("%s\n", l.p);
    // FIX: free_all hangs
    // segfaults when the strcat value is passed

    ec_strfree_all(m);

    return 0;
}
