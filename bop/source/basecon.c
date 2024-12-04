#include "shared.h"

void from_base_code_to_additional(char* n, size_t bits)
{
    for (size_t i = 1; i < bits; i++) {
        n[i] = (n[i] == '0') ? '1' : '0';
    }
    char* one = malloc(bits + 1);
    char* out = NULL;
    memset(one, '0', bits);
    one[bits] = '\0';
    one[bits - 1] = '1';
    printf("%s\n", n);
    sum(n, one, &out, bits, 0);
    free(one);

    strcpy(n, out);

    free(out);

}

void into_add_code(char* n, size_t bits)
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
