#include "system/TextureManager.hpp"

namespace fw
{

	void TextureManager::addTexture(
		const std::string& name,
		std::shared_ptr<Texture> texture
	)
	{
		m_textures[name] = texture;
	}

	std::shared_ptr<Texture> TextureManager::addTexture(
		const std::string& name,
		const std::string& path
	)
	{
		auto texture = std::make_shared<Texture>();
		texture->loadFromFile(path);
		addTexture(name, texture);
		return texture;
	}

	std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name)
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

}