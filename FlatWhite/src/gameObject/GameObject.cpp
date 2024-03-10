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

std::list<std::shared_ptr<GameObject>> GameObject::lateUpdate()
{
	std::list<std::shared_ptr<GameObject>> res;

	for (auto& component : m_components)
	{
		component->lateUpdate();
	}

	std::list<std::shared_ptr<GameObject>> childrenRes;
	for (auto& child : m_children)
	{
		if (m_moribund && child->moribundWhenParentIsMoribund())
		{
			child->setMoribund();
		}

		auto childRes = child->lateUpdate();
		for (auto& gameObject : childRes)
		{
			childrenRes.push_back(gameObject);
		}
	}

	if(m_moribund)
	{
		res = childrenRes;
		for(auto& childObject : m_children)
		{
			if (!childObject->isMoribund())
			{
				res.push_back(childObject);
			}
		}
	}
	else
	{
		for(auto& gameObject : childrenRes)
		{
			m_children.push_back(gameObject);
		}
	}

	util::removeMoribundGameObjects(m_children);

	return res;
}

//void GameObject::render(RenderTarget* window)
//{
//	for (auto& renderable : m_renderableComponents)
//	{
//		if (renderable->isVisible())
//		{
//			renderable->render(window);
//		}
//	}
//
//	for (auto& child : m_children)
//	{
//		child->render(window);
//	}
//}

void GameObject::collisionResponse(GameObject* other)
{

}

std::list<std::shared_ptr<RenderableComponent>> GameObject::getRenderableComponentsDeep()
{
	std::list<std::shared_ptr<RenderableComponent>> res;

	for (auto& child : m_children)
	{
		for (auto& renderable : child->getRenderableComponentsDeep())
		{
			res.push_back(renderable);
		}
	}

	for (auto& renderable : this->getRenderableComponentsShallow())
	{
		res.push_back(renderable);
	}

	return res;
}

//
//  PROTECTED:
//


}