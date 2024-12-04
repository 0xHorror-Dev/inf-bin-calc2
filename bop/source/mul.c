#include "shared.h"

extern int mul(const char* n1, const char* n2, char** obuf, size_t bits) {
    char* out = (char*)malloc(bits + 1);
    memset(out, '0', bits);
    out[bits] = '\0';
    uint8_t is_neg = 0;
    char* n1_tmp = (char*)malloc(bits + 1);
    strcpy(n1_tmp, n1);
    char* n2_tmp = (char*)malloc(bits + 1);
    strcpy(n2_tmp, n2);

    uint8_t overflow = 0;

    if (n1[0] == '1')
    {
        is_neg = 1;
        from_additional_code_to_base(n1_tmp, bits);
    }
    
    if (n2[0] == '1')
    {
        if (is_neg)
            is_neg = 0;
        else is_neg = 1;

        from_additional_code_to_base(n2_tmp, bits);
    }

    for (size_t i = 0, j = bits; i < bits; i += 1, j -= 1)
    {
        char c = n2_tmp[i];
        if (c == '1')
        {
            char* tmp = (char*)malloc(bits + 1);
            char* tmp2 = NULL;
            strcpy(tmp, n1_tmp);
            shift(tmp, bits, j);
            printf("%s\n", tmp);
            if (sum(tmp, out, &tmp2, bits,0) == 1)
            {
                overflow = 1;
                break;
            }

            size_t carry_count = 0;
            for (size_t k = 0; k < bits; k++) {
                if (tmp2[k] == '1') {
                    carry_count++;
                }
            }
            if (carry_count > bits) {
                overflow = 1;  // If more than 'bits' '1's, overflow has occurred
                break;
            }
            free(out);
            out = tmp2;
            free(tmp);
        }
    }

    if (is_neg)
    {
        out[0] = '1';
        from_base_code_to_additional(out, bits);
    }

    // Overflow handling
    if (overflow) {
        free(out);
        free(n1_tmp);
        free(n2_tmp);
        return 1;  // Return error code for overflow
    }

    *obuf = out;

    free(n1_tmp);
    free(n2_tmp);

    return 0; 
}