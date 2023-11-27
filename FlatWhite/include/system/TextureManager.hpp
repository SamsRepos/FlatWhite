#pragma once

#include <map>
#include <memory>
#include <string>

#include "Graphics.hpp"

namespace fw
{

	class TextureManager
	{
	public:
		void addTexture(
			const std::string& name,
			std::shared_ptr<Texture> texture
		);

		std::shared_ptr<Texture> addTexture(
			const std::string& name,
			const std::string& path
		);

		std::shared_ptr<Texture> getTexture(const std::string& name);

	private:
		std::map<std::string, std::shared_ptr<Texture>> m_textures;
	};

}