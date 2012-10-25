
#pragma once

#include "../Application.h"

namespace tetris
{
	
	class Application : public dxut::Application
	{
	public:
		explicit Application();

	protected:
		void RegisterEvents();
	};
	
};