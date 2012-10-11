
#pragma once

#include <Windows.h>

namespace dxut
{

	struct Message
	{
		explicit Message(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam)
			: hWnd(wnd),
			  msg(message),
			  wParam(wparam),
			  lParam(lparam)
		{
		}

		explicit Message() { }

		HWND   hWnd;
		UINT   msg;
		WPARAM wParam;
		LPARAM lParam;
	};

};