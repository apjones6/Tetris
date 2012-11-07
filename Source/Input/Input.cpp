
#include "../DXUT/DXUT.h"
#include "Input.h"

namespace dxut
{

	void MouseHandler::Update(double time, float elapsedTime)
	{
	}

//--------------------------------------------------------------------------------------

	void MouseHandler::OnLeftDown(WORD x, WORD y)
	{
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
	}

//--------------------------------------------------------------------------------------

	void KeyboardHandler::OnKeyUp(BYTE key)
	{
		mKeys[key] = false;
	}

};