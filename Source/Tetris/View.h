
#pragma once

#include "../Logic/Listener.h"

namespace tetris
{
	
	class ViewListener : public dxut::IListener
	{
	public:
		bool Handle(dxut::EventPtr e);
	};

};