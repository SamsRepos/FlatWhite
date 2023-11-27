#pragma once

#include <memory>

#include "gameObject/GameObject.hpp"
#include "system/Input.hpp"

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
		virtual void update(const float& deltaTime);
		virtual void lateUpdate();
		virtual void render(RenderTarget* window);

	protected:
		inline const std::list<std::shared_ptr<GameObject>>& getGameObjects() { return m_gameObjects; };

	private:
		std::list<std::shared_ptr<GameObject>> m_gameObjects;

	};

}