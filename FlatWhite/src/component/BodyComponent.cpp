#include "component/BodyComponent.hpp"

#include <cassert>

#include "gameObject/GameObject.hpp"
#include "common/Util.hpp"
#include "space/PhysicsSpace.hpp"

namespace fw
{

	BodyComponent::BodyComponent(
		GameObject* owner,
		PhysicsSpace* physicsSpace,
		int pixelsPerMetre,
		Vec2f sizeInPixels,
		BodyShape bodyShape,
		float density,
		float restitution,
		float friction,
		BodyType type
	)
		:
		Component::Component(owner),
		m_physicsSpace(physicsSpace),
		m_pixelsPerMetre(pixelsPerMetre)
	{
		auto positionInPixels = getOwner()->getPosition();
		auto positionInMetres = pixelsToMetres(positionInPixels);

		b2BodyDef bodyDef;
		bodyDef.type     = type;
		bodyDef.position = positionInMetres;
		bodyDef.angle    = getOwner()->getRotation();

		m_body = m_physicsSpace->CreateBody(&bodyDef);

		FixtureDef fixtureDef;
		float halfWidthInPixels  = sizeInPixels.x / 2.f;
		float halfHeightInPixels = sizeInPixels.y / 2.f;

		Shape* shape = nullptr;

		switch (bodyShape)
		{
		case BodyShape::Box:
		{
			auto* polyShape = new PolygonShape;
			polyShape->SetAsBox(
				pixelsToMetres(halfWidthInPixels),
				pixelsToMetres(halfHeightInPixels)
			);
			shape = polyShape;
		}
		break;
		case BodyShape::Ball:
		{
			shape = new CircleShape;
			shape->m_radius = pixelsToMetres(halfWidthInPixels);
		}
		break;
		}

		if (shape)
		{
			fixtureDef.shape = shape;
		}
		fixtureDef.density = density;
		fixtureDef.restitution = restitution;
		fixtureDef.friction = friction;

		m_fixture = m_body->CreateFixture(&fixtureDef);

		m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(getOwner());

		if (shape)
		{
			delete shape;
		}
	}

	void BodyComponent::update(const float& deltaTime)
	{
		auto* owner = getOwner();

		owner->setRotation(m_body->GetAngle());

		Vec2f positionInMetres = m_body->GetPosition();
		Vec2f positionInPixels = metresToPixels(positionInMetres);
		owner->setPosition(positionInPixels);
	}

	void BodyComponent::lateUpdate()
	{
		if (getOwner()->isMoribund())
		{
			auto* world = m_body->GetWorld();
			world->DestroyBody(m_body);
		}
	}

	void BodyComponent::setLinearVelocity(const Vec2f& velocity)
	{
		m_body->SetLinearVelocity(velocity);
	}

	const Vec2f& BodyComponent::getLinearVelocity() const
	{
		return m_body->GetLinearVelocity();
	}

	void BodyComponent::setAngularVelocity(float velocity)
	{
		m_body->SetAngularVelocity(velocity);
	}

	float BodyComponent::getAngularVelocity() const
	{
		return m_body->GetAngularVelocity();
	}

	void BodyComponent::applyForceToCentre(const Vec2f& force)
	{
		m_body->ApplyForceToCenter(force, true);
	}

	void BodyComponent::applyLinearImpulse(
		const Vec2f& impulse,
		const Vec2f& point
	)
	{
		m_body->ApplyLinearImpulse(impulse, point, true);
	}

	void BodyComponent::applyAngularImpulse(float impulse)
	{
		m_body->ApplyAngularImpulse(impulse, true);
	}

	PhysicsSpace* BodyComponent::getPhysicsSpace() const
	{
		return m_physicsSpace;
	}

	int BodyComponent::getPixelsPerMetre() const
	{
		return m_pixelsPerMetre;
	}

	bool BodyComponent::containsPointMetres(const Vec2f& pointInMetres) const
	{
		return m_fixture->TestPoint(pointInMetres);
	}

	bool BodyComponent::containsPointPixels(const Vec2f& pointInPixels) const
	{
		return containsPointMetres(pixelsToMetres(pointInPixels));
	}


	//
	// PROTECTED:
	// 

	float BodyComponent::pixelsToMetres(int pixels) const
	{
		return util::pixelsToMetres(pixels, m_pixelsPerMetre);
	}

	int BodyComponent::metresToPixels(float metres) const
	{
		return util::metresToPixels(metres, m_pixelsPerMetre);
	}

	Vec2f BodyComponent::pixelsToMetres(const Vec2f& pixels) const
	{
		return util::pixelsToMetres(pixels, m_pixelsPerMetre);
	}

	Vec2f BodyComponent::metresToPixels(const Vec2f& metres) const
	{
		return util::metresToPixels(metres, m_pixelsPerMetre);
	}

}