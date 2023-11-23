#pragma once

#include "component/Component.h"

namespace fw
{

	template<typename GameObject_T>
	class SpawnerComponent : public Component
	{
	public:
		SpawnerComponent(GameObject* owner, GameObject* parentForSpawnedObjects);

		virtual void update(const float& deltaTime);

		template<typename... ConstructorArgs_T>
		std::shared_ptr<GameObject_T> spawnObject(
			ConstructorArgs_T&&... constructorArgs
		) const;

	protected:


	private:
		GameObject* m_parentForSpawnedObjects;
	};

#include <type_traits>

	template<typename GameObject_T>
	SpawnerComponent<GameObject_T>::SpawnerComponent(GameObject* owner, GameObject* parentForSpawnedObjects)
		:
		Component(owner),
		m_parentForSpawnedObjects(parentForSpawnedObjects)
	{
		bool assertRes = std::is_base_of<GameObject, GameObject_T>();
		assert(assertRes);
	}

	template<typename GameObject_T>
	void SpawnerComponent<GameObject_T>::update(const float& deltaTime)
	{

	}

	template<typename GameObject_T>
	template<typename... ConstructorArgs_T>
	std::shared_ptr<GameObject_T> SpawnerComponent<GameObject_T>::spawnObject(
		ConstructorArgs_T&&... constructorArgs
	) const
	{
		std::shared_ptr<GameObject_T> newObject = std::make_shared<GameObject_T>(
			std::forward<ConstructorArgs_T>(constructorArgs)...
		);
		if (m_parentForSpawnedObjects) m_parentForSpawnedObjects->addChild(newObject);
		return newObject;
	}

}