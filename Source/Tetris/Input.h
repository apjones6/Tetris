
#pragma once

#include "../Input/Input.h"

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
		void OnKeyDown(BYTE key);
	};

};