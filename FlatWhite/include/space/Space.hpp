#pragma once

#include <memory>

#include "gameObject/GameObject.hpp"
#include "system/Input.hpp"
#include "common/Rectangle.hpp"

#include <list>

namespace fw
{

class Space
{
public:
	Space(const Rectangle& bounds);
	~Space();

	void addGameObject(std::shared_ptr<GameObject> gameObject);
	virtual void handleInput(const Input& input);
	virtual void update(const float& deltaTime);
	virtual void lateUpdate();
	virtual void render(RenderTarget* window);

	inline const std::list<std::shared_ptr<GameObject>>& getGameObjects() { return m_gameObjects; }; 

protected:
	inline const Rectangle& getBounds() const { return m_bounds; };

private:
	Rectangle m_bounds;
	std::list<std::shared_ptr<GameObject>> m_gameObjects;

};

}