
#pragma once

#include "Listener.h"

#include <list>
#include <map>
#include <set>

namespace dxut
{
	
	typedef std::set<EventType>	EventRegistry;

	typedef std::list<ListenerPtr> ListenerList;
	typedef std::map<EventType, ListenerList> ListenerRegistry;

//--------------------------------------------------------------------------------------

	class EventManager
	{
	public:
		void Register(EventType type);

		void AddListener(ListenerPtr listener, EventType type);
		void RemoveListener(ListenerPtr listener, EventType type);

		void Dispatch(EventPtr e);

	private:
		// Registered event types
		EventRegistry mEventRegistry;

		// Registered listeners to events
		ListenerRegistry mRegistry;
	};
	
};