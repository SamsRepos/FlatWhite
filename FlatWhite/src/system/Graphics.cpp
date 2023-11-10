#include "system/Graphics.h"

#include "common/Util.h"

void gfx::RectangleShape::setRotation(float rotation)
{
	sf::RectangleShape::setRotation(
		util::radiansToDegrees(rotation)
	);
}

float gfx::RectangleShape::getRotation() const
{
	return util::degreesToRadians(
		sf::RectangleShape::getRotation()
	);
}

void gfx::RectangleShape::setTint(const Colour& colour)
{
	sf::RectangleShape::setFillColor(colour);
}

const gfx::Colour& gfx::RectangleShape::getTint() const
{
	return sf::RectangleShape::getFillColor();
}