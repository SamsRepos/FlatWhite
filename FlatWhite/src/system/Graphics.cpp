#include "system/Graphics.h"

#include "common/Util.h"

namespace fw
{

	void RectangleShape::setRotation(float rotation)
	{
		sf::RectangleShape::setRotation(
			util::radiansToDegrees(rotation)
		);
	}

	float RectangleShape::getRotation() const
	{
		return util::degreesToRadians(
			sf::RectangleShape::getRotation()
		);
	}

	void RectangleShape::setTint(const Colour& colour)
	{
		sf::RectangleShape::setFillColor(colour);
	}

	const Colour& RectangleShape::getTint() const
	{
		return sf::RectangleShape::getFillColor();
	}

}