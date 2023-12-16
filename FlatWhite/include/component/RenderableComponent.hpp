#pragma once

#include "Component.hpp"

namespace fw
{

class RenderableComponent : public Component
{
public:
	RenderableComponent(GameObject* owner);

	void setVisible();
	void setInvisible();
	bool isVisible();

protected:
	// per frame update, callable by GameObjects:
	friend class GameObject;
	virtual void render(RenderTarget* window) = 0;

private:
	bool m_visible;
};

}