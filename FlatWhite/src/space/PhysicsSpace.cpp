#include "space/PhysicsSpace.h"

#include "gameObject/GameObject.h"
#include "common/Util.h"

namespace fw
{

//
// CONSTRUCTOR & PUBLIC:
//

PhysicsSpace::PhysicsSpace(
	const Rectangle& bounds,
	int pixelsPerMetre, 
	const Vec2f& gravity)
	:
	m_bounds(bounds),
	m_pixelsPerMetre(pixelsPerMetre),
	Space::Space(),
	b2World(gravity)
{

}


void PhysicsSpace::update(const float& deltaTime)
{
	Step(deltaTime, 1, 1);

	Space::update(deltaTime);

	// collision response calls:
	auto* contact = GetContactList();
	int contactCount = GetContactCount();

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

//fw::LineSegment PhysicsSpace::rayCast(
//	const Vec2f& startPoint, 
//	Vec2f direction
//)
//{
//	fw::Vec2f endPoint = startPoint;
//	direction.normalise();
//
//	while (m_bounds.contains(endPoint))
//	{
//		for (const std::shared_ptr<fw::GameObject>& object : getGameObjects())
//		{
//			if (object-> .contains(endPoint))
//		}
//		endPoint += direction;
//	}
//
//	return fw::LineSegment(startPoint, endPoint);
//}
//
//fw::LineSegment PhysicsSpace::rayCast(const Vec2f& startPoint, const float& angle)
//{
//	return rayCast(startPoint, util::angleToDirection(angle));
//}

//
//  PROTECTED:
//

const Rectangle& PhysicsSpace::getBounds()
{
	return m_bounds;
}

int PhysicsSpace::getPixelsPerMetre()
{
	return m_pixelsPerMetre;
}

}