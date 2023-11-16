#include "space/Space.h"

#include "common/Util.h"

namespace fw
{

	//
	//  CONSTRUCTOR/DESTRUCTOR
	//

	Space::Space()
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


	void Space::handleInput(const Input& input)
	{
		for (auto& object : m_gameObjects)
		{
			object->handleInput(input);
		}
	}


	void Space::update(float deltaTime)
	{
		for (auto& object : m_gameObjects)
		{
			object->update(deltaTime);
		}
	}

	void Space::lateUpdate()
	{
		for (auto& object : m_gameObjects)
		{
			object->lateUpdate();
		}

		util::removeMoribundGameObjects(m_gameObjects);
	}


	void Space::render(RenderTarget* window)
	{
		for (auto& object : m_gameObjects)
		{
			object->render(window);
		}
	}


	//
	//  PRIVATE:
	//

}