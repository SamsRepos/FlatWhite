#pragma once

#include <map>
#include <memory>
#include <string>

#include "Graphics.h"

class TextureManager
{
public:
	void addTexture(
		const std::string& name,
		std::shared_ptr<gfx::Texture> texture
	);
	void addTexture(
		const std::string& name,
		const std::string& path
	);
	std::shared_ptr<gfx::Texture> getTexture(const std::string& name);

private:
	std::map<std::string, std::shared_ptr<gfx::Texture>> m_textures;
};

