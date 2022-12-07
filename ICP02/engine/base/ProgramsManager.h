#pragma once
#include "Program.h"

namespace Engine 
{
	class ProgramsManager {
	public:
		void setObjectProgram(const Program& program) { object = program; }

		const Program& getObjectProgram() const { return object; }

	private:
		Program object;
	};
}
