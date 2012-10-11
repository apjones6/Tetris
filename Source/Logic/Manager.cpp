
#include "Manager.h"

#include <algorithm>

namespace dxut
{

	void EventManager::Register(EventType type)
	{
		// Ensure not registered
		const EventRegistry::const_iterator i = mEventRegistry.find(type);
		if (i != mEventRegistry.end())
		{
			throw "event type registered twice";
		}

		mEventRegistry.insert(type);
	}

//--------------------------------------------------------------------------------------

	void EventManager::AddListener(ListenerPtr listener, EventType type)
	{
		// Register event type
		if (mEventRegistry.find(type) == mEventRegistry.end())
			Register(type);

		// Get listeners
		ListenerRegistry::iterator mIt = mRegistry.find(type);
		if (mIt == mRegistry.end())
		{
			// Initialize listener list
			ListenerRegistry::value_type entry(type, ListenerList());
			mIt = mRegistry.insert(entry).first;
		}

		ListenerList& list = mIt->second;

		// Ensure listener not exists
		const ListenerList::const_iterator i = std::find(list.begin(), list.end(), listener);
		if (i != list.end())
			return;

		// Insert
		list.push_back(listener);
	}
	
//--------------------------------------------------------------------------------------

	void EventManager::RemoveListener(ListenerPtr listener, EventType type)
	{
		// Error unregistered
		if (mEventRegistry.find(type) == mEventRegistry.end())
			throw "event type not registered";

		// Skip if no listeners
		ListenerRegistry::iterator mIt = mRegistry.find(type);
		if (mIt == mRegistry.end())
			return;

		// Remove listener
		mIt->second.remove(listener);
	}
	
//--------------------------------------------------------------------------------------

	void EventManager::Dispatch(EventPtr e)
	{
		const EventType type = e->Type();

		// Error unregistered
		if (mEventRegistry.find(type) == mEventRegistry.end())
			throw "event type not registered";

		// Skip if no listeners
		ListenerRegistry::iterator mIt = mRegistry.find(type);
		if (mIt == mRegistry.end())
			return;

		ListenerList& list = mIt->second;

		// Notify listeners
		for (ListenerList::iterator lIt = list.begin(), iEnd = list.end(); lIt != iEnd; ++lIt)
			(*lIt)->Handle(e);
	}

};