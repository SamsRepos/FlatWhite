#pragma once

#include "Component.h"

namespace fw
{

	class RenderableComponent : public Component
	{
	public:
		RenderableComponent(GameObject* owner);

		virtual void render(RenderTarget* window) = 0;
	private:
	};

}