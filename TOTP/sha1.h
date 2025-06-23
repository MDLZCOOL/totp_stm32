#pragma once
#include <inttypes.h>

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

// extern union _buffer;
// extern union _state;

extern uint8_t bufferOffset;
extern uint32_t byteCount;
extern uint8_t keyBuffer[BLOCK_LENGTH];
extern uint8_t innerHash[HASH_LENGTH];

void init(void);
void initHmac(const uint8_t* secret, uint8_t secretLength);
uint8_t* result(void);
uint8_t* resultHmac(void);
void write(uint8_t);
void writeArray(uint8_t *buffer, uint8_t size);
