#pragma once

#include <SFML/Graphics.hpp>

namespace gfx
{

typedef sf::RenderTarget RenderTarget;
typedef sf::RenderWindow RenderWindow;
typedef sf::Texture      Texture;
typedef sf::Color        Colour;

class RectangleShape : public sf::RectangleShape
{
public:
	void setRotation(float rotation);
	float getRotation() const;
	void setTint(const Colour& colour);
	const Colour& getTint() const;
};


}