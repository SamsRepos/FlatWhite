#include "component/RenderableComponent.hpp"

namespace fw
{

RenderableComponent::RenderableComponent(GameObject* owner, float depth)
	:
	Component::Component(owner),
	m_visible(true),
	m_depth(depth)
{

}


void RenderableComponent::setVisible()
{
	m_visible = true;
}

void RenderableComponent::setInvisible()
{
	m_visible = false;
}

bool RenderableComponent::isVisible() const
{
	return m_visible;
}



void RenderableComponent::setDepth(float depth)
{
	m_depth = depth;
}

float RenderableComponent::getDepth() const
{
	return m_depth;
}

}