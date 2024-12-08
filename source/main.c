#include "shared.h"
//#define SEP_CONST -1
#define SEP_CONST 4

uint8_t pow2check(int32_t n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

void perform_operation(const char* x, const char* y, const uint8_t base, const char op, const size_t bits)
{
    if (!pow2check(bits))
    {
        printf("%zu not power of two!", bits);
        return;
    }


    char* xb = malloc(bits + 1);
    char* yb = malloc(bits + 1);
    char* res_buff = malloc(bits + 1);
    if (xb == NULL || yb == NULL)
    {
        printf("failed to allocate memory!");
        free(xb);
        free(yb);
        return;
    }

    strcpy_s(xb, bits + 1, x);
    strcpy_s(yb, bits + 1, y);
    uint8_t is_gneg = 0;

    if (base != 2)
    {
        uint8_t is_neg = 0;
        if (xb[0] == '-')
        {
            is_neg = 1;
            for (size_t i = 0; i < bits; i += 1)
            {
                xb[i] = xb[i + 1];
            }

        }

        is_gneg = is_neg == 1 ? 1 : 0;
        from_base_to_binary(xb, base, is_neg, res_buff, bits + 1);
        print_bin_buffer(res_buff, SEP_CONST);
        putchar('\n');
        memcpy(xb, res_buff, bits + 1);

        is_neg = 0;
        if (yb[0] == '-')
        {
            is_neg = 1;
            for (size_t i = 0; i < bits; i += 1)
            {
                yb[i] = yb[i + 1];
            }
        }

        memset(res_buff, 0, bits);
        from_base_to_binary(yb, base, is_neg, res_buff, bits + 1);
        print_bin_buffer(res_buff, SEP_CONST);
        putchar('\n');
        memcpy(yb, res_buff, bits + 1);
        is_gneg =  is_gneg || (is_neg == 1 ? 1 : 0);
    }

    free(res_buff);

    switch (op)
    {
    case '*':
        if (mul(xb, yb, &res_buff, bits) == 1)
        {
            printf("multiplication overflow!\n");
        }
        break;
    case '/':
    {
        char* q;
        if (singed_division(xb, yb, &res_buff, &q, bits) == 1)
        {
            printf("division overflow\n");
        }
        free(q);
    }
        break;
    case '+':
        if (sum(xb, yb, &res_buff, bits, 1) == 1)
        {
            if (is_gneg)
            {
                
            }
            else
            {
                printf("summate overflow!\n");
            }
        }
        break;
    case '-':
        if (substract(xb, yb, &res_buff, bits) == 1)
        {
            printf("substract overflow!");
        }
        break;
    default:
        printf("unknown operation: %c", op);
        break;
    }

    print_bin_buffer(res_buff, SEP_CONST);
    char* hex_out = NULL;
    bin_hex(res_buff, &hex_out, bits);
    putchar('|');
    puts(hex_out);
    putchar('\n');
    free(hex_out);

    free(xb);
    free(yb);
    free(res_buff);
}

int main()
{
    perform_operation("23847623876423784562378645238765428376548762354324234237642332423423423423423423423423423", "10", 10, '+', 1024);
    perform_operation("-12", "-10", 10, '*', 32);
    perform_operation("-12", "10", 10, '-', 32);
    perform_operation("116", "2", 10, '/', 32);
    perform_operation("20", "2", 10, '/', 256);
    return 0;
}