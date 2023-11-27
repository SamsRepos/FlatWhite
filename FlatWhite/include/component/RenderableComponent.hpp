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

	virtual void render(RenderTarget* window) = 0;
private:
	bool m_visible;
};

}