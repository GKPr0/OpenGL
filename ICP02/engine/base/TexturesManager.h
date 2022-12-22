#pragma once
#include <map>
#include <string>
#include "Texture.h"

namespace Engine
{
	class TexturesManager {
	public:

		void addTexture(const std::string& key, const std::string& file) { textures.insert_or_assign(key, new Texture(file)); }
		void addTexture(const std::string& key, Texture* texture) { textures.insert_or_assign(key, texture); }
		Texture* getTexture(const std::string& key) const { return textures.at(key); }

	private:
		std::map<std::string, Texture*> textures;
	};
}