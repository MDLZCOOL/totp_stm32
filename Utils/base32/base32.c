#include "base32.h"

// Base32 (RFC 4648)
static const int base32_decode_table[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, 26, 27, 28, 29, 30, 31, -1, -1, -1, -1, -1, -1, -1, -1, // 0-1, 2-7 (26-31)
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, // A-O
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // P-Z
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, // a-o (case-insensitive)
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // p-z
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

int base32_decode(const char *input, unsigned char *output) {
    size_t i, j;
    int bits;
    unsigned int buffer = 0;
    int output_idx = 0;
    size_t input_len = strlen(input);
    for (i = 0, bits = 0; i < input_len; i++) {
        int val = base32_decode_table[(unsigned char)toupper(input[i])];

        if (input[i] == '=') {
            if (i < input_len - 1 && input[i+1] != '=') {
                fprintf(stderr, "Invalid padding in Base32 string.\n");
                return -1;
            }
            break;
        }
        if (val == -1) {
            fprintf(stderr, "Invalid Base32 character: %c\n", input[i]);
            return -1;
        }
        buffer = (buffer << 5) | val;
        bits += 5;

        if (bits >= 8) {
            bits -= 8;
            output[output_idx++] = (unsigned char)(buffer >> bits);
        }
    }

    return output_idx;
}

int bytes_to_hex(const unsigned char *input, int input_len, char *output) {
    int i;
    for (i = 0; i < input_len; i++) {
        sprintf(output + (i * 2), "%02x", input[i]);
    }
    return input_len * 2;
}

int text_base32_hex(const char *text, uint8_t *output) {
    const char *base32_input = text;
    size_t max_decoded_len = (strlen(base32_input) * 5 + 7) / 8;

    unsigned char *decoded_bytes = (unsigned char *)malloc(max_decoded_len);
    if (decoded_bytes == NULL) {
        perror("Failed to allocate memory for decoded bytes");
        return 1;
    }
    int decoded_len = base32_decode(base32_input, decoded_bytes);
    if (decoded_len == -1) {
        fprintf(stderr, "Base32 decoding failed for input: %s\n", base32_input);
        free(decoded_bytes);
        return 1;
    }
    int hex_len = bytes_to_hex(decoded_bytes, decoded_len, (char *)output);
    output[hex_len] = '\0';
    free(decoded_bytes);

    return 0;
}
