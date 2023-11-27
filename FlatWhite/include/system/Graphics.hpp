#pragma once

#include <SFML/Graphics.hpp>

namespace fw
{

typedef sf::RenderTarget RenderTarget;
typedef sf::Color        Colour;
typedef sf::Vertex       Vertex;

class Texture : public sf::Texture
{
public:
	static std::shared_ptr<Texture> createPlainTexture(unsigned int width, unsigned int height);
};

class RectangleShape : public sf::RectangleShape
{
public:
	void setRotation(float rotation);
	float getRotation() const;
	void setTint(const Colour& colour);
	const Colour& getTint() const;
};


}