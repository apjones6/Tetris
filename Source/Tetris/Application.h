
#pragma once

#include "../Application.h"
#include "../Logic/Listener.h"

namespace tetris
{
	
	class Application : public dxut::ApplicationBase
	{
	public:
		explicit Application();

		void Kill();

	protected:
		void InitializeViews();

	private:
		dxut::ListenerPtr mListener;
	};
	
};