#include "space/Space.hpp"

#include "common/Util.hpp"

namespace fw
{

//
//  CONSTRUCTOR/DESTRUCTOR
//

Space::Space(Game* game, const Rectangle& bounds)
	:
	m_game(game),
	m_bounds(bounds),
	m_moribund(false)
{

}

Space::~Space()
{

}

//
//  PUBLIC:
//

void Space::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_gameObjects.push_back(gameObject);
}


//
// PROTECTED UPDATES:
//

void Space::handleInput(const Input& input)
{
	for (auto& object : m_gameObjects)
	{
		if(!object->isAwake()) continue;

		object->handleInput(input);
	}
}


void Space::update(const float& deltaTime)
{
	for (auto& object : m_gameObjects)
	{
		if(!object->isAwake()) continue;

		object->update(deltaTime);
	}
}

void Space::lateUpdate()
{
	for (auto& object : m_gameObjects)
	{
		auto gameObjectRes = object->lateUpdate();
		for (auto& gameObject : gameObjectRes)
		{
			m_gameObjects.push_back(gameObject);
		}
	}

	util::removeMoribundGameObjects(m_gameObjects);
}


void Space::render(RenderTarget* window)
{
	std::list<std::shared_ptr<RenderableComponent>> renderableBatch;

	//
	for (auto& gameObject : m_gameObjects)
	{
		if(!gameObject->isVisible()) continue;

		for (auto& renderable : gameObject->getRenderableComponentsDeep())
		{
			renderableBatch.push_back(renderable);
		}
	}

	//

	renderableBatch.sort(RenderableComponent::Comparator);

	for (auto& renderable : renderableBatch)
	{
		if(renderable->isVisible())
		{
			renderable->render(window);
		}
	}
}

//
//  PRIVATE:
//



}