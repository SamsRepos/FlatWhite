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
	};

}