#include "Audio.h"

//Audio
#include <Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

namespace Engine
{
	
	Audio::Audio(const std::string& path)
	{
		this->path = std::wstring(path.begin(), path.end());
	}

	Audio::~Audio()
	{}

	void Audio::playBlocking()
	{
		sndPlaySound(path.c_str(), SND_FILENAME);
	}

	void Audio::playNonBlocking()
	{
		sndPlaySound(path.c_str(), SND_FILENAME | SND_ASYNC);
	}

	void Audio::playNonBlockingLoop()
	{
		sndPlaySound(path.c_str(), SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}