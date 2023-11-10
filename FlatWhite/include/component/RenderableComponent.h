#pragma once

#include "Component.h"

class RenderableComponent : public Component
{
public:
	RenderableComponent(GameObject* owner);

	virtual void render(gfx::RenderTarget* window) = 0;
private:
};
