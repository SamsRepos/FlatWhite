#include "system/Window.hpp"

namespace fw
{

RenderWindow::RenderWindow(
	unsigned int width,
	unsigned int height,
	std::string title
)
	:
	sf::RenderWindow(
		sf::VideoMode(width, height),
		title
	)
{

}


void RenderWindow::pollAllEvents(Input* input)
{
	sf::Event event;
	while (pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			close();
		}
		if (fw::Input::eventIsInput(event))
		{
			input->eventUpdate(event);
		}
	}
}

}