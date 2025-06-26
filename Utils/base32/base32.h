#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

uint8_t* text_base32_decode_bytes(const char *text, int *out_len);

