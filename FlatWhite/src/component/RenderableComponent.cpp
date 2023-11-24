#include "component/RenderableComponent.h"

namespace fw
{

RenderableComponent::RenderableComponent(GameObject* owner)
	:
	Component::Component(owner),
	m_visible(true)
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

bool RenderableComponent::isVisible()
{
	return m_visible;
}

}

