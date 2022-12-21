#pragma once
#include <map>
#include <string>
#include "Texture.h"

namespace Engine
{
	class TexturesManager {
	public:

		void addTexture(const std::string& key, const std::string& file) { textures.insert_or_assign(key, Texture(file)); }
		void addTexture(const std::string& key, const Texture& texture) { textures.insert_or_assign(key, texture); }
		const Texture& getTexture(const std::string& key) const { return textures.at(key); }

	private:
		std::map<std::string, Texture> textures;
	};
}