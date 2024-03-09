#include "common/Vec3f.hpp"

namespace fw {

Vec3f::Vec3f()
	:
	Vec3f()
{

}

Vec3f::Vec3f(float x_, float y_, float z_)
	:
	Vec2f(x_, y_)
{
	z = z_;
}

Vec3f::Vec3f(sf::Vector2<float> sfVector2f)
	:
	Vec2f(sfVector2f)
{
	z = 0.f;
}

Vec3f::Vec3f(b2Vec2 b2Vec)
	:
	sf::Vector2f(b2Vec.x, b2Vec.y)
{
	z = 0.f;
}

Vec3f::operator b2Vec2() const
{
	return b2Vec2(x, y);
}

float Vec3f::magnitude() const
{
	return sqrtf(magnitudeSquared());
}


float Vec3f::magnitudeSquared() const
{
	return (x * x) + (y * y) + (z * z);
}

void Vec3f::normalise()
{
	if (isZero()) return;

	float length = magnitude();
	float recipLength = 1.f / length;

	x *= recipLength;
	y *= recipLength;
	z *= recipLength;
}

Vec3f Vec3f::normalised() const
{
	Vec3f res(x, y, z);
	res.normalise();
	return res;
}

bool Vec3f::isZero() const
{
	return ((fabsf(x) < FLT_EPSILON) && 
		    (fabsf(y) < FLT_EPSILON) && 
		    (fabsf(z) < FLT_EPSILON));
}

Vec3f Vec3f::displacementTo(const Vec3f& other) const
{
	return other - (*this);
}

Vec3f Vec3f::displacementFrom(const Vec3f& other) const
{
	return (*this) - other;
}

}