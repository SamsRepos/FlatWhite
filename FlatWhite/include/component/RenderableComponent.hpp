#pragma once

#include "Component.hpp"
#include <functional>

namespace fw
{

class RenderableComponent : public Component
{
public:
	RenderableComponent(GameObject* owner, float depth = 0.f);

	void setVisible();
	void setInvisible();
	bool isVisible() const;

	void setDepth(float depth);
	float getDepth() const;

	static bool Comparator(const std::shared_ptr<RenderableComponent> c1, const std::shared_ptr<RenderableComponent> c2)
	{
		return c1->getDepth() < c2->getDepth();
	};


protected:
	// per frame render, callable by Space:
	friend class Space;
	virtual void render(RenderTarget* window) = 0;

private:
	bool m_visible;
	float m_depth;
};

}