#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>
#include "HSL.h"
#include "RNG.h"
#include <iostream>

#define PI 3.14159265358979323846

#define RADIANS(x) ((x * PI) / 180)
#define DEGREES(x) ((x * 180) / PI)

namespace utils {

	namespace vec2 {
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

		inline float GetDirectionAngle(const sf::Vector2f& v) {

			float angleRad = atan2(v.y, v.x);
			float degrees = DEGREES(angleRad) + 90.f;

			int result = (360 + (int)round(degrees)) % 360;

			return (float)result;
		}

		inline sf::Vector2f GetNormal(const sf::Vector2f& v) {

			return sf::Vector2f(-v.y, v.x);
		}

		sf::Vector2f RotatePointAboutOrigin(const sf::Vector2f& origin, const sf::Vector2f& p, float angleInRads);
	}

	namespace color {

		sf::Color RandomizeColor(sf::Color color, float variationStrength = 10.f);

		sf::Color DarkenColor(sf::Color color, float amount, float minLuminance);

		inline float GetLuminance(sf::Color& color) {
			HSL hsl = TurnToHSL(color);

			return (float)hsl.Luminance;
		}
	}
}