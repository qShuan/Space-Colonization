#include "color.hpp"

namespace utils {

	sf::Color RandomizeColor(sf::Color color, float variationStrength) {

		HSL hsl = TurnToHSL(color);

		hsl.Hue = floor(hsl.Hue);

		hsl.Luminance = std::max(0.0f, (float)hsl.Luminance + (fastRandom() * -variationStrength));
		hsl.Saturation = std::max(0.0f, (float)hsl.Saturation + (fastRandom() * -variationStrength));

		color = hsl.TurnToRGB();

		return color;
	}
}