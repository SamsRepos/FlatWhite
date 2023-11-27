#pragma once

#include <map>

#include "Sound.hpp"

namespace fw
{

class SoundBufferManager
{
public:
	void addSoundBuffer(
		const std::string& name,
		std::shared_ptr<SoundBuffer> buffer
	);

	void addSoundBuffer(
		const std::string& name,
		const std::string& path
	);
	std::shared_ptr<SoundBuffer> getBuffer(const std::string& name);

private:
	std::map<std::string, std::shared_ptr<SoundBuffer>> m_buffers;
};

}