
#pragma once

#include "../Input/Input.h"
#include "../Views/Interface.h"

namespace tetris
{

	class MouseHandler : public dxut::MouseHandler
	{
	public:
		void OnLeftDown(WORD x, WORD y);
	};
	
//--------------------------------------------------------------------------------------
	
	class KeyboardHandler : public dxut::KeyboardHandler
	{
	public:
		explicit KeyboardHandler();

		void OnKeyDown(BYTE key);

	private:
		std::shared_ptr<dxut::Panel> mMenu;
		bool mMenuVisible;
	};

};