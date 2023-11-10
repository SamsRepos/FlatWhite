#pragma once

#include <memory>

#include "gameObject/GameObject.h"
#include "system/Input.h"

#include <list>

namespace fw
{

	class Space
	{
	public:
		Space();
		~Space();

		void addGameObject(std::shared_ptr<GameObject> gameObject);
		virtual void handleInput(const Input& input);
		virtual void update(float deltaTime);
		virtual void lateUpdate();
		virtual void render(RenderTarget* window);

	protected:
		inline const std::list<std::shared_ptr<GameObject>>& getGameObjects() { return m_gameObjects; };

	private:
		std::list<std::shared_ptr<GameObject>> m_gameObjects;

	};

}