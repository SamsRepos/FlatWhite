#include "common/Util.hpp"

#include "gameObject/GameObject.hpp"

#include <iostream>
#include <typeinfo>

namespace fw 
{

float util::pixelsToMetres(int pixels, int pixelsPerMetre)
{
	return float(pixels) / float(pixelsPerMetre);
}

int util::metresToPixels(float metres, int pixelsPerMetre)
{
	return int(metres * float(pixelsPerMetre));
}

Vec2f util::pixelsToMetres(const Vec2f& pixels, int pixelsPerMetre)
{
	return Vec2f(
		pixelsToMetres(pixels.x, pixelsPerMetre),
		pixelsToMetres(pixels.y, pixelsPerMetre)
	);
}

Vec2f util::metresToPixels(const Vec2f& metres, int pixelsPerMetre)
{
	return Vec2f(
		metresToPixels(metres.x, pixelsPerMetre),
		metresToPixels(metres.y, pixelsPerMetre)
	);
}

float util::radiansToDegrees(float radians)
{
	return radians * (180.f / PI);
}

float util::degreesToRadians(float degrees)
{
	return degrees * (PI / 180.f);
}

float util::randomFloat(
	float max,
	float min,
	int resolution
)
{
	float t = float(rand() % resolution) / float(resolution);
	return lerp(min, max, t);
}

Vec2f util::randomUnitVec2f()
{
	Vec2f res(randomFloat(1.f, -1.f), randomFloat(1.f, -1.f));
	res.normalise();
	return res;
}


float util::inverseLerp(float a, float b, float value)
{
	return (value - a) / (b - a);
}

float util::lerpAngleRad(float a, float b, float t)
{
	float angleDiff = b - a;

	if (angleDiff > PI)
	{
		angleDiff -= TWO_PI;
	}
	else if (angleDiff < -PI)
	{
		angleDiff += TWO_PI;
	}

	float angle = a + (t * angleDiff);
	return angle;
}

float util::lerpAngleDeg(float a, float b, float t)
{
	float angleDiff = b - a;

	if (angleDiff > 180.f)
	{
		angleDiff -= 360.f;
	}
	else if (angleDiff < -180.f)
	{
		angleDiff += 360.f;
	}

	float angle = a + (t * angleDiff);

	return angle;
}

float util::directionToAngle(const Vec2f& direction)
{
	return atan2f(direction.x, -direction.y);
}

Vec2f util::angleToDirection(float angle)
{
	float x = sin(angle);
	float y = -cos(angle);
	return Vec2f(x, y);
}
	
float util::dotProduct(const Vec2f& u, const Vec2f& v)
{
	return (u.x * v.x) + (u.y * v.y);
}

size_t util::removeMoribundGameObjects(std::list<std::shared_ptr<GameObject>>& gameObjects)
{
	size_t deleted_items_num = 0;

	std::list<std::shared_ptr<GameObject>>::iterator current = gameObjects.begin();
	std::list<std::shared_ptr<GameObject>>::iterator next;
	while (current != gameObjects.end()) {
		next = current;
		next++;
		if ((*current)->isMoribund()) {
			deleted_items_num++;
			//delete (*current); //delete the value at current 
			gameObjects.erase(current);
		}
		current = next;
	}

	return deleted_items_num;
}

void util::dumpGameObjectHierarchy(std::list<std::shared_ptr<fw::GameObject>> gameObjects, std::string preStr)
{
	for (auto& gameObject : gameObjects)
	{
		std::string typeStr = typeid(*(gameObject.get())).name();
		std::cout << preStr << "-- " << typeStr << std::endl;
			
		if (gameObject->getChildrenShallow().size() > 0) 
		{
			dumpGameObjectHierarchy(gameObject->getChildrenShallow(), (preStr + "  "));
		}
	}
	
}

Vec2f util::getDesktopResolution()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
	
	return Vec2f(videoMode.width, videoMode.height);
}

}