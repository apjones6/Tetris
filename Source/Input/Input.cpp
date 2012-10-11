
#include "../Application.h"
#include "../Logic/GameEvents.h"
#include "../Logic/Logic.h"
#include "../Logic/Manager.h"
#include "Input.h"

namespace dxut
{

	void MouseHandler::Update(double time, float elapsedTime)
	{
	}

//--------------------------------------------------------------------------------------

	void MouseHandler::OnLeftDown(WORD x, WORD y)
	{
		const float scale_x = (2.0f * (float)x / gApp->Width()) - 1;
		const float scale_y = 1.0f - (2.0f * (float)y / gApp->Height());

		EventPtr e(new SpawnEvent(scale_x, scale_y));
		gApp->Events()->Dispatch(e);
	}
	
//--------------------------------------------------------------------------------------

	void MouseHandler::OnLeftUp(WORD x, WORD y)
	{
	}
	
//--------------------------------------------------------------------------------------

	void MouseHandler::OnRightDown(WORD x, WORD y)
	{
	}
	
//--------------------------------------------------------------------------------------

	void MouseHandler::OnRightUp(WORD x, WORD y)
	{
	}
	
//--------------------------------------------------------------------------------------

	void MouseHandler::OnMove(WORD x, WORD y)
	{
	}
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	KeyboardHandler::KeyboardHandler()
	{
		memset(mKeys, 0, sizeof(bool) * 256);
	}
	
//--------------------------------------------------------------------------------------

	void KeyboardHandler::Update(double time, float elapsedTime)
	{
	}

//--------------------------------------------------------------------------------------

	void KeyboardHandler::OnKeyDown(BYTE key)
	{
		mKeys[key] = true;

		if (key == 'P')
		{
			TogglePause(gApp->Logic());
		}
	}

//--------------------------------------------------------------------------------------

	void KeyboardHandler::OnKeyUp(BYTE key)
	{
		mKeys[key] = false;
	}

};