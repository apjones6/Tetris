
#include "../Application.h"
#include "../Logic/GameEvents.h"
#include "../Logic/Logic.h"
#include "../Logic/Manager.h"
#include "Input.h"

namespace tetris
{

	void MouseHandler::OnLeftDown(WORD x, WORD y)
	{
		using namespace dxut;

		const float scale_x = (2.0f * (float)x / gApp->Width()) - 1;
		const float scale_y = 1.0f - (2.0f * (float)y / gApp->Height());

		EventPtr e(new SpawnEvent(scale_x, scale_y));
		gApp->Events()->Dispatch(e);
	}
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	void KeyboardHandler::OnKeyDown(BYTE key)
	{
		using namespace dxut;

		dxut::KeyboardHandler::OnKeyDown(key);

		if (key == 'P')
		{
			TogglePause(gApp->Logic());
		}
	}

};