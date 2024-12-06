#include "shared.h"

extern void from_additional_code_to_base(char* n, size_t bits)
{

    for (size_t i = 0; i < bits; i++) {
        n[i] = (n[i] == '0') ? '1' : '0';
    }

    n[bits] = '\0';
    //char* one = malloc(bits+1);
    //char* out = NULL;
    //memset(one, '0', bits+1);
    //one[bits] = '\0';
    //one[bits-1] = '1';
    //sum(n, one, &out, bits,0);
    //free(one);

    //out[bits] = '\0';
    //strcpy(n, out);

    //free(out);
}

extern void babs(char* n, size_t bits)
{
    if (n[0] == '1')
    {
        from_additional_code_to_base(n, bits);
        memmove(n, n + 1, bits + 1);
        n[0] = '0';
    }
}

extern void neg(char* n, size_t bits)
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

extern void print_bin_buffer(char* buffer, const uint8_t sep)
{
    for(size_t i = 0; buffer[i] != '\0'; i += 1)
    {
        if(i % sep == 0 && i != 0) putchar(' ');
        putchar(buffer[i]);
    }
}

void bin_hex(char* ibin, char** out_buff, size_t bits)
{
    if (ibin == NULL || *ibin == '\0') {
        return NULL;
    }

    char* bin = malloc(bits + 1);
    memset(bin, 0, 0);
    strcpy(bin, ibin);

    if (bin[0] == '1')
    {
        from_additional_code_to_base(bin, bits);
    }


    // Find the length of the binary string
    size_t binaryLen = bits;

    // Calculate the length of the hexadecimal string
    size_t hexLen = (binaryLen + 3) / 4; // Each hex digit = 4 bits
    char* hex = (char*)malloc(hexLen + 1); // Allocate memory for hex string
    if (!hex) {
        printf("allocation failed!");
        return NULL; 
    }
    hex[hexLen] = '\0'; // Null-terminate the string

    // Padding the binary string to make its length a multiple of 4
    size_t paddedLen = hexLen * 4;
    char* paddedBinary = (char*)malloc(paddedLen + 1);
    if (!paddedBinary) 
    {
        printf("allocation failed!");
        free(hex);
        return NULL; // Allocation failed
    }
    size_t padSize = paddedLen - binaryLen;
    memset(paddedBinary, '0', padSize); // Fill with leading zeros
    strcpy(paddedBinary + padSize, bin); // Copy the original binary string

    // Conversion from binary to hexadecimal
    for (size_t i = 0; i < hexLen; i++) 
    {
        char chunk[5]; // Temporary buffer for a 4-bit chunk
        strncpy(chunk, paddedBinary + i * 4, 4);
        chunk[4] = '\0'; // Null-terminate the chunk

        // Convert 4 bits to a hexadecimal digit
        int decimalValue = (chunk[0] - '0') * 8 + (chunk[1] - '0') * 4 +
            (chunk[2] - '0') * 2 + (chunk[3] - '0');
        hex[i] = decimalValue < 10 ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    *out_buff = hex;

    free(paddedBinary); 
    free(bin);
}

extern void rshift(char* binary, size_t bits, size_t shift_count) {
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

extern void shift(char* binary, size_t bits, size_t shift_count) {
    if (shift_count == 0) return;
    shift_count -= 1;
    for (size_t i = 0; i < bits - shift_count; i++) {
        binary[i] = binary[i + shift_count];
    }
    for (size_t i = bits - shift_count; i < bits; i++) {
        binary[i] = '0';
    }
}

extern void or (const char* n1, const char* n2, char** out, size_t bits)
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


void xor (const char* n1, const char* n2, char** out, size_t bits)
{
    *out = malloc(bits);
    char* rbuf = *out;

    for (size_t i = 0; i < bits; i += 1)
    {
    }
}
