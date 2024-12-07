#include "shared.h"

//gcc 7.4.0

#include  <stdio.h>

#include <stddef.h> // for size_t

void unsigned_binary_subtract(const char* n1, const char* n2, char** out, size_t bits) {
    // Allocate memory for the output
    *out = (char*)malloc(bits + 1);
    if (*out == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    (*out)[bits] = '\0'; // Null-terminate the output string

    int borrow = 0;
    for (size_t i = 0; i < bits; i++) {
        // Convert characters to integers
        int bit1 = n1[bits - 1 - i] - '0'; // Get bit from n1
        int bit2 = n2[bits - 1 - i] - '0'; // Get bit from n2

        // Perform subtraction with borrow
        int result = bit1 - bit2 - borrow;

        if (result < 0) {
            result += 2; // Borrow from the next bit
            borrow = 1;  // Set borrow for the next iteration
        }
        else {
            borrow = 0;  // No borrow needed
        }

        // Store the result bit
        (*out)[bits - 1 - i] = result + '0'; // Convert back to char
    }
}

int lbin_cmp(const char* n1, const char* n2, size_t bits) {

    // Check if the input strings are valid

    if (n1 == NULL || n2 == NULL || bits == 0 || strlen(n1) < bits || strlen(n2) < bits) {

        return 0; // Invalid input

    }


    // Compare the binary numbers bit by bit

    for (size_t i = 0; i < bits; i++) {

        char bit1 = n1[bits - 1 - i]; // Start from the least significant bit

        char bit2 = n2[bits - 1 - i]; // Start from the least significant bit


        // Compare the bits

        if (bit1 != bit2) {

            return (bit1 == '1') ? 1 : -1; // Return 1 if n1 > n2, -1 if n1 < n2

        }

    }


    // If all bits are equal, return 0

    return 0; // n1 is equal to n2

}


// Additional functions for comparisons

int bin_gt(const char* n1, const char* n2, size_t bits) {

    return lbin_cmp(n1, n2, bits) > 0;

}

int bin_ge(const char* n1, const char* n2, size_t bits) {
    return lbin_cmp(n1, n2, bits) >= 0;
}

int bin_lt(const char* n1, const char* n2, size_t bits) {
    return lbin_cmp(n1, n2, bits) < 0;
}

int bin_le(const char* n1, const char* n2, size_t bits) {
    return lbin_cmp(n1, n2, bits) <= 0;
}


void lshift(char* binary, size_t bits, size_t shift_count)
{
    if (shift_count == 0) return; // Handle no shift
    if (shift_count >= bits) { // Handle shift count larger than or equal to bits
        for (size_t i = 0; i < bits; i++) {
            binary[i] = '0';
        }
        return;
    }

    // Shift the bits to the left
    for (size_t i = 0; i < bits - shift_count; i++) {
        binary[i] = binary[i + shift_count];
    }

    // Fill the remaining bits with '0'
    for (size_t i = bits - shift_count; i < bits; i++) {
        binary[i] = '0';
    }
}

int compareBinary(const char* dividend, const char* divisor) {

    // Получаем длины строк

    int len_dividend = strlen(dividend);

    int len_divisor = strlen(divisor);


    // Сравниваем длины

    if (len_dividend < len_divisor) {

        return 0; // temp_divisor > temp_dividend

    }
    else if (len_dividend > len_divisor) {

        return 1; // temp_divisor <= temp_dividend

    }
    else {

        // Если длины равны, сравниваем поразрядно

        return strcmp(dividend, divisor) >= 0; // temp_divisor <= temp_dividend

    }

}

int compareBinaryle(const char* remainder, const char* divisor) {

    // Получаем длины строк

    int len_remainder = strlen(remainder);

    int len_divisor = strlen(divisor);


    // Сравниваем длины

    if (len_remainder < len_divisor) {

        return 0; // *remainder < temp_divisor

    }
    else if (len_remainder > len_divisor) {

        return 1; // *remainder >= temp_divisor

    }
    else {

        // Если длины равны, сравниваем поразрядно

        return strcmp(remainder, divisor) >= 0; // *remainder >= temp_divisor

    }

}


extern int unsigned_divide(const char* n1, const char* n2, char** quotient, char** remainder, size_t bits) 
{
    char* out = (char*)malloc(bits + 1);
    memset(out, '0', bits);
    out[bits] = '\0';
    uint8_t is_neg = 0;
    char* dividend = (char*)malloc(bits + 1);
    strcpy(dividend, n1);
    char* divisor = (char*)malloc(bits + 1);
    strcpy(divisor, n2);

    size_t sc = 0;
    while (compareBinary(dividend, divisor))
    {
        puts(divisor);
        lshift(divisor, bits - 1, 1);
        puts(divisor);
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
        lshift(q, bits, 1);

        if (compareBinaryle(r, divisor))
        {
            char* tmp = NULL;
            unsigned_binary_subtract(r, divisor, &tmp, bits);
            strcpy(r, tmp);
            free(tmp);

            char* qres = NULL;
            char* one = malloc(bits + 1);
            memset(one, '0', bits + 1);
            one[bits] = '\0';
            one[bits - 1] = '1';
            or (q, one, &qres, bits);
            free(one);
            memmove(q, qres, bits);
            free(qres);
        }

        rshift(divisor, bits - 1, 1);
    }


    return 0;
}


int singed_division(const char* n1, const char* n2, char** quotient, char** remainder, size_t bits)
{
    char* dividend = (char*)malloc(bits + 1);
    char* divisor = (char*)malloc(bits + 1);
    strcpy_s(dividend, bits + 1, n1);
    strcpy_s(divisor, bits + 1, n2);

     //neg(divisor, bits + 1);

     babs(dividend, bits);
     babs(divisor, bits);


     char* abs_q;
     char* abs_r;
     unsigned_divide(dividend, divisor, &abs_q, &abs_r, bits);

     if ((dividend[0] == '1') ^ (divisor[0] == '1'))
     {
         neg(abs_q, bits);
     }
     
     if(dividend[0] == '1')
     {
         neg(abs_r, bits);
     }

     *quotient = abs_q;
     *remainder = abs_r;

    free(dividend);
    free(divisor);

    strcpy(*quotient, abs_q);
    strcpy(*remainder, abs_r);
    return 0;
}


