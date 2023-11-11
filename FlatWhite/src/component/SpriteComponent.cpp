#include "component/SpriteComponent.h"

#include "gameObject/GameObject.h"
#include "common/Util.h"

namespace fw
{


	SpriteComponent::SpriteComponent(
		GameObject* owner,
		std::shared_ptr<Texture> texture
	)
		:
		RenderableComponent(owner),
		m_texture(texture)
	{
		m_rectangleShape.setTexture(m_texture.get());

		Vec2f size = Vec2f(
			m_texture->getSize().x,
			m_texture->getSize().y
		);

		m_rectangleShape.setSize(size);

		m_rectangleShape.setOrigin(size / 2.f);

		setPosition(getOwner()->getPosition());
		setRotation(getOwner()->getRotation());
	}

	void SpriteComponent::update(float deltaTime)
	{
		if (m_positionLocked)
		{
			m_rectangleShape.setPosition(getOwner()->getPosition());
		}
		if (m_rotationLocked)
		{
			m_rectangleShape.setRotation(getOwner()->getRotation());
		}
	}

	void SpriteComponent::render(RenderTarget* window)
	{
		window->draw(m_rectangleShape);
	}

	Vec2f SpriteComponent::getSize() const
	{
		return m_rectangleShape.getSize();
	}

	void SpriteComponent::setPosition(const Vec2f& position)
	{
		m_rectangleShape.setPosition(position);
	}

	const Vec2f& SpriteComponent::getPosition() const
	{
		return m_rectangleShape.getPosition();
	}

	void SpriteComponent::setRotation(float rotation)
	{
		m_rectangleShape.setRotation(rotation);
	}

	float SpriteComponent::getRotation() const
	{
		return m_rectangleShape.getRotation();
	}

	void SpriteComponent::setTint(const Colour& colour)
	{
		m_rectangleShape.setTint(colour);
	}

	const Colour& SpriteComponent::getTint() const
	{
		return m_rectangleShape.getTint();
	}



	void SpriteComponent::setPositionLocked(bool locked)
	{
		m_positionLocked = locked;
	}

	bool SpriteComponent::getPositionLocked() const
	{
		return m_positionLocked;
	}

	void SpriteComponent::setRotationLocked(bool locked)
	{
		m_rotationLocked = locked;
	}

	bool SpriteComponent::getRotationLocked() const
	{
		return m_rotationLocked;
	}

	void SpriteComponent::setTexture(std::shared_ptr<Texture> texture)
	{
		m_texture = texture;
		m_rectangleShape.setTexture(m_texture.get());
	}

}