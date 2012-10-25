
#include "../Logic/GameEvents.h"
#include "../Logic/Manager.h"
#include "Application.h"
#include "Logic.h"

namespace tetris
{
	
	Application::Application()
		: dxut::ApplicationBase(std::shared_ptr<dxut::LogicBase>(new tetris::Logic))
	{
	}

//--------------------------------------------------------------------------------------

	void Application::RegisterEvents()
	{
		Events()->Register(dxut::EVENT_ACTOR_CREATED);
		Events()->Register(dxut::EVENT_SPAWN_ACTOR);
	}

};