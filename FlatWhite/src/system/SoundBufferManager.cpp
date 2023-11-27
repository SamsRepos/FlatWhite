#include "system/SoundBufferManager.hpp"

namespace fw
{

void SoundBufferManager::addSoundBuffer(
	const std::string& name,
	std::shared_ptr<SoundBuffer> buffer
)
{
	m_buffers[name] = buffer;
}

void SoundBufferManager::addSoundBuffer(
	const std::string& name,
	const std::string& path
)
{
	auto buffer = std::make_shared<SoundBuffer>();
	buffer->loadFromFile(path);
	addSoundBuffer(name, buffer);
}

std::shared_ptr<SoundBuffer> SoundBufferManager::getBuffer(const std::string& name)
{
	if (m_buffers.find(name) == m_buffers.end())
	{
		return nullptr;
	}
	else
	{
		return m_buffers[name];
	}
}

}