#pragma once

#include <stdint.h>

namespace utils {

	namespace rng {

		static uint32_t s_rngSeed = 2463534242;

		inline uint32_t XorShift32() {
			s_rngSeed ^= s_rngSeed << 13;
			s_rngSeed ^= s_rngSeed >> 17;
			s_rngSeed ^= s_rngSeed << 5;
			return s_rngSeed;
		}

		// Fast random float between 0 and 1
		inline float FastRandom() {
			return (XorShift32() & 0xFFFFFF) / 16777215.0f;  // Normalized to 0-1
		}

		inline float RandomBetween(float from, float to) {
			return from + (to - from) * FastRandom();
		}
	}
}