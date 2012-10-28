
#pragma once

#include "../Application.h"
#include "../Logic/Listener.h"

namespace tetris
{
	
	class Application : public dxut::ApplicationBase
	{
	public:
		explicit Application();

		void Initialize(const std::wstring& title, bool windowed = true, int width = 800, int height = 600);
		void Kill();

	protected:
		void RegisterEvents();

	private:
		dxut::ListenerPtr mListener;
	};
	
};