#include "shared.h"

void babs(char* n, size_t bits)
{
    if (n[0] == '1')
    {
        from_additional_code_to_base(n, bits);
    }
}

void neg(char* n, size_t bits)
{
    if (n[0] == '1')
    {
        
    }
    else
    {
        n[0] = '1';
        from_base_code_to_additional(n, bits);
    }

}

void print_bin_buffer(char* buffer)
{
    for(size_t i = 0; buffer[i] != '\0'; i += 1)
    {
        //if(i % 4 == 0 && i != 0) putchar(' ');
        putchar(buffer[i]);
    }
    putchar('\n');
}

void xor (const char* n1, const char* n2, char** out, size_t bits)
{
    *out = malloc(bits);
    char* rbuf = *out;

    for (size_t i = 0; i < bits; i += 1)
    {
    }
}

void rshift(char* binary, size_t bits, size_t shift_count) {
    if (shift_count == 0) return;

    // Adjust the shift_count if it's greater than the number of bits
    shift_count = (shift_count > bits) ? bits : shift_count;

    // Perform the shift by moving the bits to the right
    for (size_t i = bits - 1; i >= shift_count; i--) {
        binary[i] = binary[i - shift_count];
    }

    // Pad the leftmost bits with '0'
    for (size_t i = 0; i < shift_count; i++) {
        binary[i] = '0';
    }
}

void shift(char* binary, size_t bits, size_t shift_count) {
    if (shift_count == 0) return;
    shift_count -= 1;
    for (size_t i = 0; i < bits - shift_count; i++) {
        binary[i] = binary[i + shift_count];
    }
    for (size_t i = bits - shift_count; i < bits; i++) {
        binary[i] = '0';
    }
}

void or (const char* n1, const char* n2, char** out, size_t bits)
{
    *out = malloc(bits + 1);
    char* o = *out;


    for (size_t i = 0; i < bits; i += 1)
    {
        char c1 = n1[i];
        char c2 = n2[i];
        o[i] = (c1 == '1' || c2 == '1') ? '1' : '0';
    }

    o[bits] = '\0';
}
