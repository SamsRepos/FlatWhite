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

		virtual void update(const float& deltaTime) = 0;
		virtual void lateUpdate() { };

	protected:
		inline GameObject* getOwner() const { return m_owner; };

	private:
		GameObject* m_owner;
	};

}