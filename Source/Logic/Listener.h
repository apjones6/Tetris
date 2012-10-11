
#pragma once

#include "Event.h"

namespace dxut
{
	
	class IListener
	{
	public:
		virtual bool Handle(EventPtr e) = 0;
		virtual ~IListener() { }
	};

//--------------------------------------------------------------------------------------

	typedef std::shared_ptr<IListener> ListenerPtr;

};