#include "shared.h"

extern int sum(const char* n1, const char* n2, char** obuf, size_t bits, uint8_t overflow_save)
{
    // Allocate memory for the result buffer (bits + 1 for carry + 1 for null terminator)
    char* buf = malloc(bits + 2);
    if (buf == NULL)
        return -1;

    // Initialize the buffer with '0' and null-terminate it
    memset(buf, '0', bits + 1);
    buf[bits + 1] = '\0'; // Null terminator at the end

    uint8_t carry = 0; // Carry bit
    size_t i = bits;

    // Perform binary addition from the least significant bit to the most significant bit
    while (i > 0)
    {
        --i; // Decrement index to process from right to left
        uint8_t bit1 = (n1[i] == '1') ? 1 : 0; // Convert '1' to 1, '0' to 0
        uint8_t bit2 = (n2[i] == '1') ? 1 : 0;

        // Compute sum and carry
        uint8_t sum = bit1 + bit2 + carry;
        buf[i + 1] = (sum % 2) + '0'; // Store the result as '0' or '1'
        carry = sum / 2;              // Update carry (1 if sum >= 2, otherwise 0)
    }

    // Handle the final carry (most significant bit)
    buf[0] = carry + '0'; // If carry is 1, buf[0] = '1'; otherwise '0'

    if (carry && overflow_save)
    {
        // If overflow_save is true, keep the carry in the result
        *obuf = buf;
        return 1; // Indicate overflow occurred
    }
    else if (carry)
    {
        // If overflow_save is false, discard the carry
        memmove(buf, buf + 1, bits + 1); // Shift left to remove the leading '1'
    }
    else
    {
        // If no carry, shift left to remove the leading '0'
        memmove(buf, buf + 1, bits + 1);
    }

    *obuf = buf; // Set output buffer
    return carry ? 1 : 0; // Return 1 if overflow occurred, otherwise 0
}


