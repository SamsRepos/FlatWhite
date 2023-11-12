#pragma once

#include "component/Component.h"

#include "system/Sound.h"

namespace fw {

class GameObject;

class SoundComponent : public Component
{
public:
	SoundComponent(GameObject* owner);
	
	void createAndAddSoundInstance(const std::string& name, std::shared_ptr<SoundBuffer> soundBuffer);
	void addSoundInstance(const std::string& name, const SoundInstance& soundInstaance);

	virtual void update(float deltaTime);

	void playSound(const std::string& name);

private:
	std::map<std::string, SoundInstance> m_soundInstances;
};

}