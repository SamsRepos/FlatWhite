#pragma once

#include <list>
#include <memory>

#include "component/RenderableComponent.hpp"

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
	
	//
	inline Vec2f getPosition() { return m_position; };
	inline void  setPosition(const Vec2f& position) { m_position = position; };
	inline float getRotation() { return m_rotation; };
	inline void  setRotation(float rotation) { m_rotation = rotation; };

	inline void setAwake(bool awake) { m_awake = m_awakeOnNextFrame = awake; };
	inline void setAwakeOnNextFrame(bool awake) { m_awakeOnNextFrame = awake; }
	inline bool isAwake() { return m_awake; };

	inline void setVisible(bool visible) { m_visible = m_visibleOnNextFrame = visible; };
	inline void setVisibleOnNextFrame(bool visible) { m_visibleOnNextFrame = visible; };
	inline bool isVisible() { return m_visible; };

	inline void setMoribund() { m_moribund = true; };
	inline bool isMoribund() { return m_moribund; };

	inline void setMoribundWhenParentIsMoribund(bool b) { m_moribundWhenParentIsMoribund = b; };
	inline bool moribundWhenParentIsMoribund() { return m_moribundWhenParentIsMoribund; };

	inline std::list<std::shared_ptr<GameObject>>& getChildrenShallow() { return m_children; };
	inline std::list<std::shared_ptr<Component>>& getComponentsShallow() { return m_components; };
	inline std::list<std::shared_ptr<RenderableComponent>>& getRenderableComponentsShallow() { return m_renderableComponents; };
	std::list<std::shared_ptr<RenderableComponent>> getRenderableComponentsDeep();

protected:
	// per frame functions, called by Space:
	friend class Space;
	virtual void handleInput(const Input& input);
	virtual void update(const float& deltaTime);
	virtual std::list<std::shared_ptr<GameObject>> lateUpdate();
	// called by PhysicsSpace:
	friend class PhysicsSpace;
	virtual void collisionResponse(GameObject* other);
	
private:
	std::list<std::shared_ptr<GameObject>> m_children;
	std::list<std::shared_ptr<Component>> m_components;
	std::list<std::shared_ptr<RenderableComponent>> m_renderableComponents;
	Vec2f m_position; // in pixels
	float m_rotation; // in radians

	bool m_visible             = true;
	bool m_visibleOnNextFrame  = true;

	bool m_awake               = true;
	bool m_awakeOnNextFrame    = true;

	bool m_moribund                     = false; // set to true when game object is to be deleted at the end of the current frame
	bool m_moribundWhenParentIsMoribund = true;
};

}