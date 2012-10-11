
#pragma once

#include <memory>

namespace dxut
{
	
	typedef unsigned long EventType;
	
//--------------------------------------------------------------------------------------
	
	class IEvent
	{
	public:
		virtual EventType Type() const = 0;
		virtual ~IEvent() { }
	};
	
//--------------------------------------------------------------------------------------
	
	typedef std::shared_ptr<IEvent>	EventPtr;

};