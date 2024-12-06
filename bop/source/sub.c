#include <shared.h>

extern int substract(const char* n1, const char* n2, char** obuf, size_t bits)
{
    if (bin_cmp(n1, n2, bits) == 0)
    {
        char* buff = malloc(bits + 1);
        memset(buff, '0', bits);
        buff[bits] = '\0';
        *obuf = buff;
        return 0;
    }

    //char* inv_n2 = malloc(bits + 1);  // Allocate space for the null-terminator
    //if (inv_n2 == NULL) return -1;    // Check for memory allocation failure

    //// Invert the bits
    //for (size_t i = 0; i < bits; ++i) {
    //    inv_n2[i] = (n2[i] == '1') ? '0' : '1';
    //}
    //inv_n2[bits] = '\0';  // Add the null-terminator

    //int result;
    //char* temp_buf = NULL;
    //if (n2[0] == '0') {
    //    char* one = malloc(bits + 1);  // Allocate space for the null-terminator
    //    if (one == NULL) {  // Check for memory allocation failure
    //        free(inv_n2);   // Clean up
    //        return -1;
    //    }

    //    memset(one, '0', bits);  // Initialize with '0's
    //    one[bits] = '\0';         // Null-terminate the string
    //    one[bits - 1] = '1';      // Set the last bit to '1'

    //    result = sum(inv_n2, one, &temp_buf, bits, 0);
    //    //if (result != 0) {
    //    //    free(inv_n2);
    //    //    free(one);
    //    //    return -1;
    //    //}

    //    free(one);  // Free the temporary one buffer
    //}

    //if (temp_buf == NULL) {
    //    free(inv_n2);  // Clean up if temp_buf was not properly set
    //    return -1;
    //}

    //// Assuming obuf is already allocated before this point
    //result = sum(n1, temp_buf, obuf, bits, 1);

    //free(inv_n2);
    //free(temp_buf);

    //return result;

        // Allocate space for the inverted n2
    char* inv_n2 = malloc(bits + 1);
    if (inv_n2 == NULL) return -1; // Check for memory allocation failure
    strcpy(inv_n2, n2);


    int result;
    char* temp_buf = NULL;

    // Check if we need to add 1 to the inverted n2 (for two's complement)
    if (n2[0] == '0') {
        // Invert the bits of n2
        for (size_t i = 0; i < bits; ++i) {
            inv_n2[i] = (n2[i] == '1') ? '0' : '1';
        }
        inv_n2[bits] = '\0'; // Null-terminate the string

        // Allocate space for the string representing 1
        char* one = malloc(bits + 1);
        if (one == NULL) { // Check for memory allocation failure
            free(inv_n2); // Clean up
            return -1;
        }

        memset(one, '0', bits);  // Initialize with '0's
        one[bits] = '\0';         // Null-terminate the string
        one[bits - 1] = '1';      // Set the last bit to '1'

        // Perform the addition of the inverted n2 and '1' (two's complement)
        result = sum(inv_n2, one, &temp_buf, bits, 0);

        //free(temp_buf);
        free(one);  // Free the temporary 'one' buffer

        if (result != 0) { // Check for addition failure
            //free(inv_n2);
            return -1;
        }
    }
    else if (n2[0] == '1')
    {
        // Invert the bits of n2
        for (size_t i = 0; i < bits; ++i) {
            inv_n2[i] = (n2[i] == '1') ? '0' : '1';
        }
        inv_n2[bits] = '\0'; // Null-terminate the string

        // Allocate space for the string representing 1
        char* one = malloc(bits + 1);
        if (one == NULL) { // Check for memory allocation failure
            free(inv_n2); // Clean up
            return -1;
        }

        memset(one, '0', bits);  // Initialize with '0's
        one[bits] = '\0';         // Null-terminate the string
        one[bits - 1] = '1';      // Set the last bit to '1'

        // Perform the addition of the inverted n2 and '1' (two's complement)
        result = sum(inv_n2, one, &temp_buf, bits, 0);
        free(one);  // Free the temporary 'one' buffer

        if (result != 0) { // Check for addition failure
            free(inv_n2);
            return -1;
        }
    }
    else {
        // If n2 is already negative or zero, use it as is
        temp_buf = inv_n2;
    }

    if (temp_buf == NULL) {
        free(inv_n2);  // Clean up if temp_buf was not set
        return -1;
    }

    *obuf = malloc(bits+1);

    // Perform the subtraction (n1 + temp_buf)
    result = sum(n1, temp_buf, obuf, bits, 1);
    if (result == 1)
    {
        memmove(*obuf, (*obuf) + 1, bits + 1);
    }
    
    free(inv_n2);
    free(temp_buf); // Only free temp_buf if it was dynamically allocated (if sum function allocates it)

    return result;
}
