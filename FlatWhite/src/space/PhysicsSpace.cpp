#include "space/PhysicsSpace.h"

#include "gameObject/GameObject.h"

namespace fw
{

	PhysicsSpace::PhysicsSpace(int pixelsPerMetre, Vec2f gravity)
		:
		m_pixelsPerMetre(pixelsPerMetre),
		Space::Space()
	{
		m_world = std::make_shared<b2World>(gravity);
	}

	PhysicsSpace::~PhysicsSpace()
	{

		/*if (world)
		{
			delete world;
			world = nullptr;
		}*/
	}

	void PhysicsSpace::update(float deltaTime)
	{
		m_world->Step(deltaTime, 1, 1);

		Space::update(deltaTime);

		// collision response calls:
		auto* contact = m_world->GetContactList();
		int contactCount = m_world->GetContactCount();

		for (int contactNum = 0; contactNum < contactCount; ++contactNum)
		{
			if (contact->IsTouching())
			{
				// get the colliding bodies
				b2Body* bodyA = contact->GetFixtureA()->GetBody();
				b2Body* bodyB = contact->GetFixtureB()->GetBody();

				GameObject* objA = nullptr;
				GameObject* objB = nullptr;

				uintptr_t ptrA = bodyA->GetUserData().pointer;
				uintptr_t ptrB = bodyB->GetUserData().pointer;

				objA = reinterpret_cast<GameObject*>(ptrA);
				objB = reinterpret_cast<GameObject*>(ptrB);

				if (objA)
				{
					objA->collisionResponse(objB);
				}
				if (objB)
				{
					objB->collisionResponse(objA);
				}
			}
			// Get next contact point
			contact = contact->GetNext();
		}
	}

}