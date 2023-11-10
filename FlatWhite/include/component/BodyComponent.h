#pragma once

#include "Component.h"

#include "system/Physics.h"

namespace fw {

	enum class BodyShape
	{
		Box,
		Ball
	};

	class BodyComponent : public Component
	{
	public:
		BodyComponent(
			GameObject* owner,
			World* world,
			int pixelsPerMetre,
			Vec2f sizeInPixels,
			BodyShape bodyShape,
			float density,
			float restitution,
			float friction,
			BodyType type = b2_dynamicBody
		);

		virtual void update(float deltaTime);
		virtual void lateUpdate();

		void setLinearVelocity(const Vec2f& velocity);
		const Vec2f& getLinearVelocity() const;
		void setAngularVelocity(float velocity);
		float getAngularVelocity() const;

		World* getWorld() const;
		int getPixelsPerMetre() const;

		bool containsPointMetres(const Vec2f& pointInMetres) const;
		bool containsPointPixels(const Vec2f& pointInPixels) const;

	protected:
		inline Body* getBody() { return m_body; };

		float pixelsToMetres(int pixels) const;
		int metresToPixels(float metres) const;

		Vec2f pixelsToMetres(const Vec2f& pixels) const;
		Vec2f metresToPixels(const Vec2f& metres) const;

	private:
		Body* m_body;
		Fixture* m_fixture;

		int m_pixelsPerMetre;
	};

}