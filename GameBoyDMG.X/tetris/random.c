/* 
 * File:   random.c
 * Author: Jacob Malin
 *
 * Created on December 3, 2024, 10:19 PM
 */

#include "random.h"

static uint32_t x, y, z, w;

void Random(void) {
    uint16_t seed = TCB0.CNT;
    x = seed;
    y = seed + 42;
    z = seed - 42;
    w = seed * 42;
}

uint32_t _Random_xorshift128(void) {
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

uint8_t Random_generate(uint8_t upper) {
    uint32_t rand_num = _Random_xorshift128() % upper;
    return rand_num;
}

uint8_t Random_generate_avoid(uint8_t upper, uint8_t avoid) {
    uint32_t rand_num;
    uint8_t attempts = 0;
    
    // For rand_num attempts, generate a number that is not avoid
    do {
        rand_num = _Random_xorshift128() % upper;
    } while (rand_num == avoid && ++attempts < RAND_MAX_ATTEMPTS);
    
    return rand_num;
}

void Random_add_random(void) {
    x += TCB0.CNT; // Add TCB clock count to increase randomness via user input
}