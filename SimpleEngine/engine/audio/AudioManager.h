#pragma once
#include "Audio.h"
#include <map>
#include <string>



namespace Engine
{
	class AudioManager{
	public:
		void addAudio(const std::string& key, const std::string& path) { this->audio.insert_or_assign(key, new Audio(path)); }
		Audio* getAudio(const std::string& key) const { return this->audio.at(key); }

	private:
		std::map<std::string, Audio*> audio;
	};
}
