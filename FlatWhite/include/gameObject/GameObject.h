#pragma once

#include <list>
#include <memory>

#include "component/RenderableComponent.h"

namespace fw
{

class GameObject
{
public:
	GameObject(
		const Vec2f& initialPosition = Vec2f(0.f, 0.f),
		float initialRotation = 0.f
	);

	//
	void addChild(std::shared_ptr<GameObject> child);
	void addComponent(std::shared_ptr<Component> component);

	// per frame functions:
	virtual void handleInput(const Input& input);
	virtual void update(float deltaTime);
	virtual void lateUpdate();
	virtual void render(RenderTarget* window);

	//
	virtual void collisionResponse(GameObject* other);

	//
	inline Vec2f getPosition() { return m_position; };
	inline void  setPosition(const Vec2f& position) { m_position = position; };
	inline float getRotation() { return m_rotation; };
	inline void  setRotation(float rotation) { m_rotation = rotation; };

	inline void setMoribund() { m_moribund = true; };
	inline bool isMoribund() { return m_moribund; };

protected:
	std::list<std::shared_ptr<GameObject>>& getChildren();

private:
	std::list<std::shared_ptr<GameObject>> m_children;
	std::list<std::shared_ptr<Component>> m_components;
	std::list<std::shared_ptr<RenderableComponent>> m_renderableComponents;
	Vec2f m_position; // in pixels
	float m_rotation; // in radians

	bool m_moribund = false; // set to true when game object is to be deleted at the end of the current frame
};

}