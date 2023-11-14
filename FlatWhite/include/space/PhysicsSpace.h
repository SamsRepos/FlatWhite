#pragma once

#include "space/Space.h"

#include "common/Vec2f.h"
#include "system/Physics.h"

namespace fw
{

	class PhysicsSpace : public Space
	{
	public:
		PhysicsSpace(int pixelsPerMetre = 1, Vec2f gravity = Vec2f(0.f, 9.81f));
		~PhysicsSpace();
		virtual void update(float deltaTime);

	protected:
		std::shared_ptr<World> getWorld() { return m_world; };

	private:
		std::shared_ptr<World> m_world;
		int m_pixelsPerMetre;
	};

}