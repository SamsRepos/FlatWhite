#pragma once

#include "space/Space.h"

#include "common/Vec2f.h"
#include "system/Physics.h"
#include "common/Rectangle.h"

namespace fw
{

class PhysicsSpace : public Space, public b2World
{
public:
	PhysicsSpace(
		const Rectangle& bounds,
		int pixelsPerMetre = 1,
		const Vec2f& gravity = Vec2f(0.f, 9.81f)
	);

	virtual void update(float deltaTime);

protected:
	//std::shared_ptr<World> getWorld() { return m_world; };
	const Rectangle& getBounds();
	int getPixelsPerMetre();

private:
	//std::shared_ptr<World> m_world;
	Rectangle m_bounds;
	int m_pixelsPerMetre;
};

}