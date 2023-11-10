#pragma once

#include <memory>
#include <list>

#include "Vec2f.h"

const float DEFAULT_RANDOM_FLOAT_RESOLUTION = 1000;

class GameObject;

namespace util
{
	const float PI        = 3.14159265358f;
	const float TWO_PI    = PI * 2.f;
	const float PI_BY_TWO = PI / 2.f;

	float pixelsToMetres(int pixels, int pixelsPerMetre);
	int metresToPixels(float metres, int pixelsPerMetre);

	Vec2f pixelsToMetres(Vec2f pixels, int pixelsPerMetre);
	Vec2f metresToPixels(Vec2f metres, int pixelsPerMetre);

	float radiansToDegrees(float radians);
	float degreesToRadians(float degrees);

	float randomFloat(
		float max = 1.f, 
		float min = 0.f,
		int resolution = DEFAULT_RANDOM_FLOAT_RESOLUTION
	);
	Vec2f randomUnitVec2f();

	template<typename T>
	T lerp(T a, T b, float t)
	{
		return ((1 - t) * a) + (t * b);
	};

	float inverseLerp(float a, float b, float value);
	float lerpAngleRad(float a, float b, float t);
	float lerpAngleDeg(float a, float b, float t);

	size_t deleteMoribundGameObjects(std::list<std::shared_ptr<GameObject>>& gameObjects);

	// for polymorphic inheritance only
	template<typename Base, typename Derived> bool isType(Base* basePtr)
	{
		Derived* checkPtr = dynamic_cast<Derived*>(basePtr);
		if (checkPtr) return true;
		else return false;
	};
	
	// for polymorphic inheritance only
	template<typename Base, typename Derived> bool isType(std::shared_ptr<Base> basePtr)
	{
		return isType<Base, Derived>(basePtr.get());
	};



	
}

