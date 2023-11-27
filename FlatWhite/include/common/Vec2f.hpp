#pragma once

#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>

namespace fw {

class Vec2f : public sf::Vector2f
{
public:
	Vec2f();
	Vec2f(float xAndY);
	Vec2f(float x, float y);
	//Vec2f(sf::Vector2f& sfVector2f);
	Vec2f(sf::Vector2<float> sfVector2f);
	//Vec2f(b2Vec2& b2Vec);
	Vec2f(b2Vec2 b2Vec);
	operator b2Vec2() const;

	float magnitude() const;
	float magnitudeSquared() const;

	void normalise();
	Vec2f normalised() const;

	bool isZero() const;

	Vec2f displacementTo(const Vec2f& other) const;
	Vec2f displacementFrom(const Vec2f& other) const;

	inline static Vec2f zero()      { return Vec2f(0.f); };
	inline static Vec2f unitLeft()  { return Vec2f(-1.f, 0.f); };
	inline static Vec2f unitRight() { return Vec2f(1.f,  0.f); };
	inline static Vec2f unitUp()    { return Vec2f(0.f,  -1.f); };
	inline static Vec2f unitDown()  { return Vec2f(0.f,  1.f); };
};

}