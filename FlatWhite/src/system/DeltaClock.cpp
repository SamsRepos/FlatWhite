#include "system/DeltaClock.h"

namespace fw
{

float DeltaClock::getDeltaTime()
{
	return restart().asSeconds();
}

}