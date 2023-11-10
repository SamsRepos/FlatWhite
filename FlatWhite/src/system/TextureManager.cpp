#include "system/TextureManager.h"

void TextureManager::addTexture(
	const std::string& name,
	std::shared_ptr<gfx::Texture> texture
)
{
	m_textures[name] = texture;
}

void TextureManager::addTexture(
	const std::string& name,
	const std::string& path
)
{
	auto texture = std::make_shared<gfx::Texture>();
	texture->loadFromFile(path);
	addTexture(name, texture);
}

std::shared_ptr<gfx::Texture> TextureManager::getTexture(const std::string& name)
{
	if (m_textures.find(name) == m_textures.end())
	{
		return nullptr;
	}
	else
	{
		return m_textures[name];
	}
}