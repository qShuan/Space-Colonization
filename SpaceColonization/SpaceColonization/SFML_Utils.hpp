#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace utils {

	namespace vector2f {
		// Returns the magnitude (length) of a 2D vector
		inline float GetVectorMagnitude(const sf::Vector2f& v) {

			return sqrt((v.y * v.y) + (v.x * v.x));
		}

		// Returns a normalized version of a 2D vector (unit vector)
		inline sf::Vector2f VectorNormalize(const sf::Vector2f& v) {

			sf::Vector2f newVector = v;

			float mag = GetVectorMagnitude(v);

			if (mag == 0)
				return sf::Vector2f(0.f, 0.f);

			return newVector / mag;
		}

		// Returns the Z-component of the 3D cross product of two 2D vectors
		inline float ZCrossProduct(const sf::Vector2f& a, const sf::Vector2f& b) {

			return ((a.x * b.y) - (a.y * b.x));
		}
	}
}