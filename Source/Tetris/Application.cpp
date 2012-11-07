
#include "../Logic/GameEvents.h"
#include "../Logic/Manager.h"
#include "../Views/HumanView.h"
#include "Application.h"
#include "Input.h"
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

	void Application::Kill()
	{
		// Detach listeners
		Events()->RemoveListener(mListener, dxut::EVENT_ACTOR_CREATED);

		ApplicationBase::Kill();
	}

//--------------------------------------------------------------------------------------

	void Application::InitializeViews()
	{
		using namespace dxut;

		// Initialize input handlers
		std::shared_ptr<IKeyboardHandler> keyboard(new KeyboardHandler);
		std::shared_ptr<IMouseHandler> mouse(new MouseHandler);

		// Initialize views
		std::shared_ptr<IView> view(new HumanView(keyboard, mouse));
		Logic()->AddView(view);

		// Attach view listeners
		Events()->AddListener(mListener, dxut::EVENT_ACTOR_CREATED);
	}
	
};