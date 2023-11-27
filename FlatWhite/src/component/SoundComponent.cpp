#include "component/SoundComponent.hpp"

namespace fw
{

SoundComponent::SoundComponent(GameObject* owner)
	:
	Component(owner)
{

}

void SoundComponent::createAndAddSoundInstance(
	const std::string& name, 
	std::shared_ptr<SoundBuffer> soundBuffer
)
{

	m_soundInstances[name] = SoundInstance(*(soundBuffer.get()));
}

void SoundComponent::addSoundInstance(
	const std::string& name, 
	const SoundInstance& soundInstaance
)
{
	m_soundInstances[name] = soundInstaance;
}

void SoundComponent::update(const float& deltaTime)
{

}

void SoundComponent::playSound(const std::string& name)
{
	if (m_soundInstances.find(name) == m_soundInstances.end())
	{
		return;
	}
	else
	{
		m_soundInstances[name].play();
	}
}

}