#include "gameObject/GameObject.hpp"

#include "common/Util.hpp"

namespace fw
{

//
// PUBLIC CONSTRUCTOR & INIT:
//

GameObject::GameObject(const Vec2f& initialPosition, float initialRotation)
	:
	m_position(initialPosition),
	m_rotation(initialRotation)
{
}

void GameObject::addChild(std::shared_ptr<GameObject> child)
{
	m_children.push_back(child);
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
	m_components.push_back(component);

	if (util::isType<Component, RenderableComponent>(component))
	{
		std::shared_ptr<RenderableComponent> renderable = std::reinterpret_pointer_cast<RenderableComponent>(component);
		m_renderableComponents.push_back(renderable);
	}
}

//
// PUBLIC UPDATES:
//

void GameObject::handleInput(const Input& input)
{
	for (auto& child : m_children)
	{
		child->handleInput(input);
	}
}

void GameObject::update(const float& deltaTime)
{
	for (auto& component : m_components)
	{
		component->update(deltaTime);
	}

	for (auto& child : m_children)
	{
		child->update(deltaTime);
	}
}

void GameObject::lateUpdate()
{
	for (auto& component : m_components)
	{
		component->lateUpdate();
	}

	for (auto& child : m_children)
	{
		child->lateUpdate();
	}

	util::removeMoribundGameObjects(m_children);
}

void GameObject::render(RenderTarget* window)
{
	for (auto& renderable : m_renderableComponents)
	{
		if(renderable->isVisible())
		{
			renderable->render(window);
		}
	}

	for (auto& child : m_children)
	{
		child->render(window);
	}
}

void GameObject::collisionResponse(GameObject* other)
{

}

//
//  PROTECTED:
//



}