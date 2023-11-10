#pragma once

#include "component/Component.h"

template<typename GameObject_T>
class SpawnerComponent : public Component
{
public:
	SpawnerComponent(GameObject* owner);

	virtual void update(float deltaTime);

	template<typename... ConstructorArgs_T>
	std::shared_ptr<GameObject_T> spawnObject(
		ConstructorArgs_T&&... constructorArgs
	) const;

protected:


private:
};

#include <type_traits>

template<typename GameObject_T>
SpawnerComponent<GameObject_T>::SpawnerComponent(GameObject* owner)
	:
	Component(owner)
{
	bool assertRes = std::is_base_of<GameObject, GameObject_T>();
	assert(assertRes);
}

template<typename GameObject_T>
void SpawnerComponent<GameObject_T>::update(float deltaTime)
{

}

template<typename GameObject_T>
template<typename... ConstructorArgs_T>
std::shared_ptr<GameObject_T> SpawnerComponent<GameObject_T>::spawnObject(
	ConstructorArgs_T&&... constructorArgs
) const
{
	return std::make_shared<GameObject_T>(
		std::forward<ConstructorArgs_T>(constructorArgs)...
	);
}