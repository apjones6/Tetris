
#include "Application.h"
#include "../Logic/GameEvents.h"
#include "../Logic/Logic.h"
#include "../Logic/Manager.h"

namespace tetris
{
	
	Application::Application()
		: dxut::Application(std::shared_ptr<dxut::EventManager>(new dxut::EventManager), std::shared_ptr<dxut::BaseLogic>(new dxut::BaseLogic))
	{
	}

//--------------------------------------------------------------------------------------

	void Application::RegisterEvents()
	{
		Events()->Register(dxut::EVENT_ACTOR_CREATED);
		Events()->Register(dxut::EVENT_SPAWN_ACTOR);
	}

};