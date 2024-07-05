#pragma once

#include "space/Space.hpp"

#include "common/Vec2f.hpp"
#include "system/Physics.hpp"
#include "common/Rectangle.hpp"
#include "common/LineSegment.hpp"

namespace fw
{

class PhysicsSpace : public Space, public b2World
{
public:
	PhysicsSpace(
		Game* game,
		const Rectangle& bounds,
		int pixelsPerMetre = 1,
		const Vec2f& gravity = Vec2f(0.f, 9.81f)
	);

protected:
	virtual void update(const float& deltaTime);

	int getPixelsPerMetre();
	
private:
	int m_pixelsPerMetre;

	//fw::LineSegment rayCast(const Vec2f& startPoint, Vec2f direction);
	//fw::LineSegment rayCast(const Vec2f& startPoint, const float& angle);
};

}