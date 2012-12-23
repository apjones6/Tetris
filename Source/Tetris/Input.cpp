
#include "../Application.h"
#include "../Logic/Manager.h"
#include "Input.h"
#include "Logic.h"

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

	KeyboardHandler::KeyboardHandler()
		: mMenu(new dxut::Panel(-0.6f, -0.6f, 0.6f, 0.6f, dxut::PURPLE)),
		  mMenuVisible(false)
	{
	}

//--------------------------------------------------------------------------------------
	
	void KeyboardHandler::OnKeyDown(BYTE key)
	{
		using namespace dxut;

		dxut::KeyboardHandler::OnKeyDown(key);

		if (key == 'Q')
		{
			if (mMenuVisible)
			{
				gApp->Logic()->HumanView()->RemoveView(mMenu);
			}
			else
			{
				mMenu->Initialize();
				gApp->Logic()->HumanView()->AddView(mMenu);
			}
			
			mMenuVisible = !mMenuVisible;
			gApp->Logic()->SetPaused(mMenuVisible);
		}
		
		if (key == 'P' && !mMenuVisible)
		{
			TogglePause(gApp->Logic());
		}
	}

};