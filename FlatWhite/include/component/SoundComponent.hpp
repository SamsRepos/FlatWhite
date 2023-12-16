#pragma once

#include "component/Component.hpp"

#include "system/Sound.hpp"

namespace fw {

class GameObject;

class SoundComponent : public Component
{
public:
	SoundComponent(GameObject* owner);
	
	void createAndAddSoundInstance(const std::string& name, std::shared_ptr<SoundBuffer> soundBuffer);
	void addSoundInstance(const std::string& name, const SoundInstance& soundInstaance);

	void playSound(const std::string& name);

protected:
	virtual void update(const float& deltaTime);

private:
	std::map<std::string, SoundInstance> m_soundInstances;
};

}