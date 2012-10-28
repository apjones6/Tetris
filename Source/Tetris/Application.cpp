
#include "../Logic/GameEvents.h"
#include "../Logic/Manager.h"
#include "Application.h"
#include "Logic.h"
#include "View.h"

namespace tetris
{
	
	Application::Application()
		: dxut::ApplicationBase(std::shared_ptr<dxut::LogicBase>(new tetris::Logic)),
		  mListener(new ViewListener)
	{
	}
	
//--------------------------------------------------------------------------------------

	void Application::Initialize(const std::wstring& title, bool windowed, int width, int height)
	{
		ApplicationBase::Initialize(title, windowed, width, height);
		Events()->AddListener(mListener, dxut::EVENT_ACTOR_CREATED);
	}
	
//--------------------------------------------------------------------------------------

	void Application::Kill()
	{
		Events()->RemoveListener(mListener, dxut::EVENT_ACTOR_CREATED);
		ApplicationBase::Kill();
	}

//--------------------------------------------------------------------------------------

	void Application::RegisterEvents()
	{
		Events()->Register(dxut::EVENT_ACTOR_CREATED);
		Events()->Register(dxut::EVENT_SPAWN_ACTOR);
	}

};