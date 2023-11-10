#pragma once

#include "RenderableComponent.h"

class SpriteComponent : public RenderableComponent
{
public:
	SpriteComponent(
		GameObject* owner,
		std::shared_ptr<gfx::Texture> texture
	);

	virtual void update(float deltaTime);
	virtual void render(gfx::RenderTarget* window);

	Vec2f getSize() const;

	void setPosition(const Vec2f& position);
	const Vec2f& getPosition() const;
	void setRotation(float rotation);
	float getRotation() const;
	void setTint(const gfx::Colour& colour);
	const gfx::Colour& getTint() const;

	void setPositionLocked(bool locked);
	bool getPositionLocked() const;
	void setRotationLocked(bool locked);
	bool getRotationLocked() const;

private:
	std::shared_ptr<gfx::Texture> m_texture;
	gfx::RectangleShape m_rectangleShape;

	bool m_positionLocked = true;
	bool m_rotationLocked = true;
};

