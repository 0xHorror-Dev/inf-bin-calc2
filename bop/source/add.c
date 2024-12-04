#include "shared.h"

int sum(const char* n1, const char* n2, char** obuf, size_t bits, uint8_t overflow_save)
{
    // Allocate memory for the result buffer (plus one for null terminator, plus one for carry)
    char* buf = malloc(bits + 2);
    if (buf == NULL)
        return -1;

    // Initialize the buffer with '0' and null-terminate it
    memset(buf, '0', bits + 1);  // Initialize with zeros
    buf[bits + 1] = '\0';         // Null terminator at the end

    uint8_t carry = 0;            // Carry bit
    size_t i = bits;

    // Perform binary addition from least significant bit (rightmost) to most significant
    while (i > 0)
    {
        --i; // Decrement index to process from right to left
        uint8_t bit1 = n1[i] - '0'; // Convert char to int ('0' to 0, '1' to 1)
        uint8_t bit2 = n2[i] - '0';

        // Calculate the sum and the new carry
        uint8_t sum = bit1 + bit2 + carry;
        buf[i + 1] = (sum % 2) + '0'; // Store the result ('0' or '1')
        carry = sum / 2;              // Update carry (1 if sum >= 2, otherwise 0)
    }

    // Handle final carry (most significant bit)
    if (carry)
        buf[0] = '1';
    else
        buf[0] = '0';

    // If there is an overflow and overflow_save is true, shift the result to the right
    if (buf[0] == '1')
    {
        if (overflow_save)
        {
            memmove(buf, buf + 1, bits + 1); // Discard the leading 1 and save the rest
        }
        *obuf = buf; // Return the result, including the overflow bit
        return 1;     // Indicate that there was overflow
    }
    else
    {
        // If no overflow, shift the result to the left to remove the leading '0'
        memmove(buf, buf + 1, bits + 1);
        *obuf = buf; // Return the result
    }

    return 0; // Success
}

void xor (const char* n1, const char* n2, char** out, size_t bits)
{
    *out = malloc(bits);
    char* rbuf = *out;

    for (size_t i = 0; i < bits; i += 1)
    {
    }
}

