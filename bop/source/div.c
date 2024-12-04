#include "shared.h"

int divide(const char* n1, const char* n2, char** quotient, char** remainder, size_t bits) {

    char* out = (char*)malloc(bits + 1);
    memset(out, '0', bits);
    out[bits] = '\0';
    uint8_t is_neg = 0;
    char* dividend = (char*)malloc(bits + 1);
    strcpy(dividend, n1);
    char* divisor = (char*)malloc(bits + 1);
    strcpy(divisor, n2);

    size_t sc = 0;
    while (bin_cmp(divisor, dividend, bits) == -1)
    {
        shift(divisor, bits, 2);
        sc += 1;
    }

    rshift(divisor, bits, 1);
    sc -= 1;

    *quotient = (char*)malloc(bits + 1);
    memset(*quotient, '0', bits);
    (*quotient)[bits] = '\0';

    char* q = *quotient;

    *remainder = (char*)malloc(bits + 1);
    strcpy(*remainder, n1);
    char* r = *remainder;
    
    for (size_t i = 0; i <= sc; i += 1)
    {
        shift(q, bits, 2);

        if (bin_cmp(r, divisor, bits) >= 0)
        {
            char* tmp = NULL;
            substract(r, divisor, &tmp, bits);
            memmove(r, tmp, bits);
            free(tmp);

            char* qres = NULL;
            char* one = malloc(bits + 1);
            memset(one, '0', bits + 1);
            one[bits] = '\0';
            one[bits - 1] = '1';
            or(q, one, &qres, bits);
            free(one);
            memmove(q, qres, bits);
            free(qres);
        }

        rshift(divisor, bits, 1);
    }


    return 0;
}
