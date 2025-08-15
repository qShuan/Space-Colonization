#include "SFML_Utils.hpp"

namespace utils {

	namespace vector2f {

		sf::Vector2f RotatePointAboutOrigin(const sf::Vector2f& origin, const sf::Vector2f& p, float angleInRads) {

			float s = sin(angleInRads);
			float c = cos(angleInRads);

			sf::Vector2f rotatedPoint;

			rotatedPoint.x = p.x - origin.x;
			rotatedPoint.y = p.y - origin.y;

			float newX = c * rotatedPoint.x - s * rotatedPoint.y;
			float newY = s * rotatedPoint.x + c * rotatedPoint.y;

			rotatedPoint.x = newX + origin.x;
			rotatedPoint.y = newY + origin.y;

			return rotatedPoint;
		}
	}

	namespace color {

		sf::Color RandomizeColor(sf::Color color, float variationStrength) {

			HSL hsl = TurnToHSL(color);

			hsl.Hue = floor(hsl.Hue);

			hsl.Luminance = std::max(0.0f, (float)hsl.Luminance + (fastRandom() * -variationStrength));
			hsl.Saturation = std::max(0.0f, (float)hsl.Saturation + (fastRandom() * -variationStrength));

			color = hsl.TurnToRGB();

			return color;
		}
	}
}