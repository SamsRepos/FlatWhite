#pragma once

#include "Vec2f.hpp"

namespace fw
{

class Vec3f : public Vec2f
{
public:
	Vec3f();
	Vec3f(float x, float y, float z);
	Vec3f(sf::Vector2<float> sfVector2f);
	Vec3f(b2Vec2 b2Vec);

	float magnitude() const;
	float magnitudeSquared() const;

	void normalise();
	Vec3f normalised() const;

	bool isZero() const;

	Vec3f displacementTo(const Vec2f& other) const;
	Vec3f displacementFrom(const Vec2f& other) const;

	inline static Vec3f zero()      { return Vec3f(0.f); };
	inline static Vec3f unitLeft()  { return Vec3f(-1.f, 0.f); };
	inline static Vec2f unitRight() { return Vec3f(1.f,  0.f); };
	inline static Vec3f unitUp()    { return Vec3f(0.f,  -1.f); };
	inline static Vec3f unitDown()  { return Vec3f(0.f,  1.f); };

private:
	float z;
};

}