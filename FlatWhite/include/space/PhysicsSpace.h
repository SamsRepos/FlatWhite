#pragma once

#include "space/Space.h"

#include "common/Vec2f.h"

namespace fw
{

	class PhysicsSpace : public Space
	{
	public:
		PhysicsSpace(int pixelsPerMetre = 1, Vec2f gravity = Vec2f(0.f, 9.81f));
		~PhysicsSpace();
		virtual void update(float deltaTime);

	protected:
		std::shared_ptr<b2World> getWorld() { return m_world; };

	private:
		std::shared_ptr<b2World> m_world;
		int m_pixelsPerMetre;
	};

}