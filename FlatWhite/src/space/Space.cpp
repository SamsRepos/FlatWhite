#include "space/Space.h"

#include "common/Util.h"

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

	util::deleteMoribundGameObjects(m_gameObjects);
}


void Space::render(gfx::RenderTarget* window)
{
	for (auto& object : m_gameObjects)
	{
		object->render(window);
	}
}


//
//  PRIVATE:
//
