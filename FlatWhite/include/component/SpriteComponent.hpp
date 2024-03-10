#pragma once

#include "RenderableComponent.hpp"

#include "common/Rectangle.hpp"

namespace fw
{
	class SpriteComponent : public RenderableComponent
	{
	public:
		SpriteComponent(
			GameObject* owner,
			std::shared_ptr<Texture> texture,
			float depth = 0
		);

		void setSize(const Vec2f& size);
		Vec2f getSize() const;

		void setPosition(const Vec2f& position);
		const Vec2f& getPosition() const;
		void setRotation(float rotation);
		float getRotation() const;
		void setTint(const Colour& colour);
		const Colour& getTint() const;

		const Rectangle& getGlobalBounds();
		bool contains(Vec2f point);

		void setPositionLocked(bool locked);
		bool getPositionLocked() const;
		void setRotationLocked(bool locked);
		bool getRotationLocked() const;

		void setTexture(std::shared_ptr<Texture> texture);
		const std::shared_ptr<Texture>& getTexture() const;
	protected:
		virtual void update(const float& deltaTime);
		virtual void render(RenderTarget* window);

	private:
		std::shared_ptr<Texture> m_texture;
		RectangleShape m_rectangleShape;

		bool m_positionLocked = true;
		bool m_rotationLocked = true;
	};

}