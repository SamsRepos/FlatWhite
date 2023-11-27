#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Input.hpp"

namespace fw
{

class RenderWindow : public sf::RenderWindow
{
public:
	RenderWindow(
		unsigned int width,
		unsigned int height,
		std::string title
	);

	void pollAllEvents(Input* input);

private:
};
}