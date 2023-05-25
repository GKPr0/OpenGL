#pragma once
#include <string>

namespace Engine
{
	class Audio {
	public:
		Audio(const std::string& path);
		~Audio();

		void playBlocking();
		void playNonBlocking();
		void playNonBlockingLoop();
	
	private:
		std::wstring path;
	};
}