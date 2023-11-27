#include "system/DeltaClock.hpp"

namespace fw
{

float DeltaClock::getDeltaTime()
{
	return restart().asSeconds();
}

}