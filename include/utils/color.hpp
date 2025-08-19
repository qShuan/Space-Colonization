#pragma once

#include <SFML/Graphics/Color.hpp>
#include <utils/rng.hpp>
#include "../SpaceColonization/HSL.h"

namespace utils {

	namespace color {

		sf::Color Randomize(sf::Color color, float variationStrength = 10.f);

		inline sf::Color Darken(sf::Color color, float amount, float minLuminance) {

			HSL hsl = TurnToHSL(color);
			hsl.Luminance = std::max(minLuminance, (float)hsl.Luminance - amount);
			color = hsl.TurnToRGB();

			return color;
		}

		inline float GetLuminance(const sf::Color& color) {
			HSL hsl = TurnToHSL(color);

			return (float)hsl.Luminance;
		}
	}
}