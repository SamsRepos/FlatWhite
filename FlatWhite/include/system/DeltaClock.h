#pragma once

#include <SFML/System/Clock.hpp>

namespace fw
{

class DeltaClock : private sf::Clock
{
public:
	float getDeltaTime(); // seconds

private:
};

}