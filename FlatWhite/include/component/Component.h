#pragma once

#include "common/Vec2f.h"
#include "system/Graphics.h"
#include "system/Input.h"

namespace fw
{

	class GameObject;

	class Component
	{
	public:
		Component(GameObject* owner);

		virtual void update(const float& deltaTime) = 0;
		virtual void lateUpdate() { };

	protected:
		inline GameObject* getOwner() const { return m_owner; };

	private:
		GameObject* m_owner;
	};

}