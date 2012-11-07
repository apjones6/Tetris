
#pragma once

namespace dxut
{

	class IMouseHandler
	{
	public:
		virtual ~IMouseHandler() { }

		virtual void Update(double time, float elapsedTime) = 0;

		virtual void OnLeftDown(WORD x, WORD y) = 0;
		virtual void OnLeftUp(WORD x, WORD y) = 0;
		virtual void OnRightDown(WORD x, WORD y) = 0;
		virtual void OnRightUp(WORD x, WORD y) = 0;
		virtual void OnMove(WORD x, WORD y) = 0;
	};
	
//--------------------------------------------------------------------------------------
	
	class IKeyboardHandler
	{
	public:
		virtual ~IKeyboardHandler() { }

		virtual void Update(double time, float elapsedTime) = 0;

		virtual void OnKeyDown(BYTE key) = 0;
		virtual void OnKeyUp(BYTE key) = 0;
	};

//--------------------------------------------------------------------------------------

	class MouseHandler : public IMouseHandler
	{
	public:
		explicit MouseHandler() { }

		void Update(double time, float elapsedTime);

		void OnLeftDown(WORD x, WORD y);
		void OnLeftUp(WORD x, WORD y);
		void OnRightDown(WORD x, WORD y);
		void OnRightUp(WORD x, WORD y);
		void OnMove(WORD x, WORD y);
	};
	
//--------------------------------------------------------------------------------------
	
	class KeyboardHandler : public IKeyboardHandler
	{
	public:
		explicit KeyboardHandler();

		void Update(double time, float elapsedTime);

		void OnKeyDown(BYTE key);
		void OnKeyUp(BYTE key);

	protected:
		bool mKeys[256];
	};

};