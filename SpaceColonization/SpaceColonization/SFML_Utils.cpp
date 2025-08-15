#include "SFML_Utils.hpp"

namespace utils {

	namespace color {

		sf::Color RandomizeColor(sf::Color color) {

			HSL hsl = TurnToHSL(color);

			hsl.Hue = floor(hsl.Hue);

			constexpr float color_variation = 10.0f;

			hsl.Luminance = std::max(0.0f, (float)hsl.Luminance + (fastRandom() * -color_variation));
			hsl.Saturation = std::max(0.0f, (float)hsl.Saturation + (fastRandom() * -color_variation));

			color = hsl.TurnToRGB();

			return color;
		}
	}
}