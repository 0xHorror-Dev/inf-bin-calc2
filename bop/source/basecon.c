#include "shared.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>




extern int bin_cmp(const char* n1, const char* n2, size_t bits) {

    // Compare bit by bit
    for (size_t i = 0; i < bits; ++i) {
        if (n1[i] > n2[i]) {
            return 1;  // n1 is greater than n2
        }
        else if (n1[i] < n2[i]) {
            return -1; // n1 is less than n2
        }
    }

    return 0;  // n1 is equal to n2
}



// Function to multiply a decimal string by a base and add a digit (to handle large numbers)
inline void multiply_and_add(char* result, int base, int digit_value) {
    int carry = 0;
    int length = strlen(result);

    for (int i = length - 1; i >= 0; i--) {
        int value = (result[i] - '0') * base + carry;
        if (i == length - 1) value += digit_value; // Add digit value to the last position
        result[i] = (value % 10) + '0';
        carry = value / 10;
    }

    // Handle overflow by shifting the result
    if (carry > 0) {
        memmove(result + 1, result, length + 1);
        result[0] = carry + '0';
    }
}

// Convert the decimal string to binary
inline void decimal_to_binary(const char* decimal, char* binary_result, size_t bin_res_size, uint8_t is_neg) {
    memset(binary_result, '0', bin_res_size);
    binary_result[bin_res_size - 1] = '\0'; // Null-terminate the binary string

    char temp[512];
    strncpy(temp, decimal, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    int binary_index = bin_res_size - 2; // Start filling binary from the second last position

    // Perform repeated division by 2
    while (strlen(temp) > 0 && !(strlen(temp) == 1 && temp[0] == '0')) {
        int remainder = 0;
        char next_temp[512] = { 0 };
        int next_index = 0;

        for (int i = 0; i < strlen(temp); i++) {
            int current = remainder * 10 + (temp[i] - '0');
            next_temp[next_index++] = (current / 2) + '0';
            remainder = current % 2;
        }

        // Remove leading zeros in the next_temp
        int start = 0;
        while (next_temp[start] == '0' && start < next_index - 1) {
            start++;
        }

        strncpy(temp, next_temp + start, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';

        if (binary_index < 0) {
            printf("Error: Binary result buffer too small to store the result.\n");
            return;
        }

        binary_result[binary_index--] = remainder + '0';
    }

    // Fill the remaining positions with leading zeros
    while (binary_index >= 0) {
        binary_result[binary_index--] = '0';
    }
}

// Apply two's complement if the number is negative
inline void apply_twos_complement(char* binary_result, size_t bin_res_size) {
    // Flip the bits
    for (size_t i = 0; i < bin_res_size - 1; i++) {
        binary_result[i] = (binary_result[i] == '0') ? '1' : '0';
    }

    // Add 1 to the binary number
    int carry = 1;
    for (int i = bin_res_size - 2; i >= 0 && carry > 0; i--) {
        if (binary_result[i] == '1') {
            binary_result[i] = '0';
        }
        else {
            binary_result[i] = '1';
            carry = 0;
        }
    }
}

// Main conversion function
extern void from_base_to_binary(const char* base_number, int base, uint8_t is_neg, char* binary_result, size_t bin_res_size) {
    char decimal[512] = "0"; // Store as a decimal string

    for (size_t i = 0; i < strlen(base_number); i++) {
        char digit = base_number[i];
        int digit_value;

        if (isdigit(digit)) {
            digit_value = digit - '0';
        }
        else if (isalpha(digit)) {
            digit_value = toupper(digit) - 'A' + 10;
        }
        else {
            printf("Invalid digit '%c' in the number for base %d\n", digit, base);
            return;
        }

        multiply_and_add(decimal, base, digit_value);
    }

    // Convert decimal string to binary
    decimal_to_binary(decimal, binary_result, bin_res_size, is_neg);

    // Apply two's complement if the number is negative
    if (is_neg) {
        apply_twos_complement(binary_result, bin_res_size);
    }
}

extern void from_base_code_to_additional(char* n, size_t bits)
{
    char* one = malloc(bits + 1);
    char* out = NULL;
    memset(one, '0', bits);
    one[bits] = '\0';
    one[bits - 1] = '1';
    printf("%s\n", n);
    sum(n, one, &out, bits, 0);
    free(one);

    for (size_t i = 0; i < bits; i++) {
        out[i] = (out[i] == '0') ? '1' : '0';
    }

    strcpy(n, out);

    free(out);
}

extern  void into_add_code(char* n, size_t bits)
{
    char* inv_n2 = malloc(bits + 1);  // Allocate space for the null-terminator
    if (inv_n2 == NULL) {
        fprintf(stderr, "Memory allocation failed for inv_n2\n");
        return;
    }
    inv_n2[bits] = '\0';  // Null-terminate inv_n2

    // Invert the bits
    for (long long i = bits - 1; i >= 0;i-=1) {
        char c = n[i];
        inv_n2[i] = (c == '1') ? '0' : '1';
    }

    int result;
    char* temp_buf = NULL;

    // Allocate memory for adding "1" to the inverted value
    char* one = malloc(bits + 1);
    if (one == NULL) {
        free(inv_n2);   // Clean up
        fprintf(stderr, "Memory allocation failed for one\n");
        return;
    }

    memset(one, '0', bits);  // Initialize with '0's
    one[bits] = '\0';         // Null-terminate the string
    one[bits - 1] = '1';      // Set the last bit to '1'

    result = sum(inv_n2, one, &temp_buf, bits, 0);
    if (result != 0) {
        free(inv_n2);
        free(one);
        fprintf(stderr, "Sum operation failed\n");
        return;
    }

    // Copy the result to n
    strcpy(n, temp_buf);
    free(inv_n2);
    free(one);
    free(temp_buf);  // Free temp_buf when done
}
