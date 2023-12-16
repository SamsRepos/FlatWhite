#pragma once

#include "common/Vec2f.hpp"
#include "system/Graphics.hpp"
#include "system/Input.hpp"

namespace fw
{

class GameObject;

class Component
{
public:
	Component(GameObject* owner);

protected:
	// per frame functions, called by Space:
	friend class GameObject;
	virtual void update(const float& deltaTime) = 0;
	virtual void lateUpdate() { };

	inline GameObject* getOwner() const { return m_owner; };

private:
	GameObject* m_owner;
};

}