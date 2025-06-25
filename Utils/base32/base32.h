#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int bytes_to_hex(const unsigned char *input, int input_len, char *output);
int base32_decode(const char *input, unsigned char *output);
int text_base32_hex(const char *text, uint8_t *output);

