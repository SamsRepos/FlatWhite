#include "system/Graphics.hpp"

#include "common/Util.hpp"

namespace fw
{
	std::shared_ptr<Texture> Texture::createPlainTexture(unsigned int width, unsigned  int height)
	{
		std::vector<sf::Uint8> imageArray;
		imageArray.reserve(width * height);
		sf::Image image;
		image.create(width, height, imageArray.data());
		auto tex = std::make_shared<Texture>();
		tex->loadFromImage(image);
		return tex;
	}

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