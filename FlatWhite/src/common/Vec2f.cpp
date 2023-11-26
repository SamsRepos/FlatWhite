#include "common/Vec2f.h"

namespace fw {

Vec2f::Vec2f()
	:
	sf::Vector2f()
{

}

Vec2f::Vec2f(float xAndY)
	:
	sf::Vector2f(xAndY, xAndY)
{

}

Vec2f::Vec2f(float x_, float y_)
	:
	sf::Vector2f(x_, y_)
{

}

//Vec2f::Vec2f(sf::Vector2f& sfVector2f)
//	:
//	sf::Vector2f(sfVector2f)
//{
//	
//}

Vec2f::Vec2f(sf::Vector2<float> sfVector2f)
	:
	sf::Vector2f(sfVector2f)
{

}

//Vec2f::Vec2f(b2Vec2& b2Vec)
//	:
//	sf::Vector2f(b2Vec.x, b2Vec.y)
//{
//
//}

Vec2f::Vec2f(b2Vec2 b2Vec)
	:
	sf::Vector2f(b2Vec.x, b2Vec.y)
{

}

Vec2f::operator b2Vec2() const
{
	return b2Vec2(x, y);
}

float Vec2f::magnitude() const
{
	return sqrtf((x * x) + (y * y));
}


float Vec2f::magnitudeSquared() const
{
	return (x * x) + (y * y);
}

void Vec2f::normalise()
{
	if (isZero()) return;

	float length = magnitude();
	float recipLength = 1.f / length;

	x *= recipLength;
	y *= recipLength;
}

Vec2f Vec2f::normalised() const
{
	Vec2f res(x, y);
	res.normalise();
	return res;
}

bool Vec2f::isZero() const
{
	return (fabsf(x) < FLT_EPSILON) && (fabsf(y) < FLT_EPSILON);
}

}