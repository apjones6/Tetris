
#pragma once

#include "Event.h"
#include "Logic.h"

namespace dxut
{
	
	const EventType EVENT_ACTOR_CREATED = 1;
	const EventType EVENT_SPAWN_ACTOR = 2;
	
//--------------------------------------------------------------------------------------

	class ActorEvent : public IEvent
	{
	public:
		explicit ActorEvent(const ActorId id);

		EventType Type() const { return EVENT_ACTOR_CREATED; }
		ActorId Actor() const { return mId; }

	private:
		const ActorId mId;
	};
	
//--------------------------------------------------------------------------------------

	class SpawnEvent : public IEvent
	{
	public:
		explicit SpawnEvent(float x, float y);

		EventType Type() const { return EVENT_SPAWN_ACTOR; }
		float X() const { return mX; }
		float Y() const { return mY; }

	private:
		const float mX, mY;
	};

};