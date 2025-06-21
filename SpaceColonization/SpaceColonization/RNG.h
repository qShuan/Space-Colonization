#pragma once

#include <stdint.h>

static uint32_t rng_seed = 2463534242;

inline uint32_t xorshift32() {
	rng_seed ^= rng_seed << 13;
	rng_seed ^= rng_seed >> 17;
	rng_seed ^= rng_seed << 5;
	return rng_seed;
}

// Fast random float between 0 and 1
inline float fastRandom() {
	return (xorshift32() & 0xFFFFFF) / 16777215.0f;  // Normalized to 0-1
}

inline float randomBetween(float from, float to)
{
	return from + (to - from) * fastRandom();
}