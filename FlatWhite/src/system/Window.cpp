#include "system/Window.hpp"

namespace fw
{

namespace
{
	sf::Uint32 getStyle(bool startFullScreen, bool windowAdjustable)
	{
		sf::Uint32 res = sf::Style::None;

		res |= sf::Style::Close;

		if(startFullScreen)
		{
			res |= sf::Style::Fullscreen;
		}

		if(windowAdjustable)
		{
			res |= sf::Style::Resize;
		}

		return res;
	}


}

RenderWindow::RenderWindow(
	unsigned int width,
	unsigned int height,
	std::string title,
	bool startFullscreen,
	bool windowAdjustable
)
	:
	sf::RenderWindow(
		sf::VideoMode(width, height),
		title,
		getStyle(startFullscreen, windowAdjustable)
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