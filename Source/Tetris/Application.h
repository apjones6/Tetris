
#pragma once

#include "../Application.h"

namespace tetris
{
	
	class Application : public dxut::ApplicationBase
	{
	public:
		explicit Application();

	protected:
		void RegisterEvents();
	};
	
};