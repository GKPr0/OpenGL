#pragma once
#include "Program.h"
#include <map>

namespace Engine 
{
	class ProgramsManager {
	public:

		void addProgram(const std::string& key, const std::string& vertFile, const std::string& fragFile) { programs.insert_or_assign(key, Program(vertFile, fragFile)); }
		void addProgram(const std::string& key, const Program& program) { programs.insert_or_assign(key, program); }
		const Program& getProgram(const std::string& key) const { return programs.at(key); }

	private:
		std::map<std::string, Program> programs;
	};
}
