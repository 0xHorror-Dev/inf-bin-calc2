#pragma once
#include <stdint.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void babs(char* n, size_t bits);
void neg(char* n, size_t bits);

extern int mul(const char* n1, const char* n2, char** obuf, size_t bits);
extern int singed_division(const char* n1, const char* n2, char** quotient, char** remainder, size_t bits);
extern int unsinged_division(const char* n1, const char* n2, char** quotient, char** remainder, size_t bits);
extern int substract(const char* n1, const char* n2, char** obuf, size_t bits);
extern int sum(const char* n1, const char* n2, char** obuf, size_t bits, uint8_t overflow_save);

extern void into_base_code(char* n, size_t bits);
extern void into_add_code(char* n, size_t bits);
extern int bin_cmp(const char* n1, const char* n2, size_t bits);
extern void rshift(char* binary, size_t bits, size_t shift_count);
extern void shift(char* binary, size_t bits, size_t shift_count);
extern void or (const char* n1, const char* n2, char** out, size_t bits);

extern void print_bin_buffer(char* buffer, uint8_t sep);
