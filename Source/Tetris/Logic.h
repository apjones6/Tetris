
#pragma once

#include "../Logic/Event.h"
#include "../Logic/Listener.h"
#include "../Logic/Logic.h"

namespace tetris
{
	
	const dxut::ActorType ACTOR_TYPE_SQUARE = 1;
	const dxut::ActorType ACTOR_TYPE_TRIANGLE = 2;
	
//--------------------------------------------------------------------------------------
	
	const dxut::EventType EVENT_ACTOR_CREATED = 1;
	const dxut::EventType EVENT_SPAWN_ACTOR = 2;

//--------------------------------------------------------------------------------------

	class Logic : public dxut::LogicBase
	{
	public:
		explicit Logic();

		void Initialize();
		void Update(double time, float elapsedTime);

		void AddActor(std::shared_ptr<dxut::Actor> actor);
	};
	
//--------------------------------------------------------------------------------------

	class LogicListener : public dxut::IListener
	{
	public:
		bool Handle(dxut::EventPtr e);
	};
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

	class ActorEvent : public dxut::IEvent
	{
	public:
		explicit ActorEvent(const dxut::ActorId id);

		dxut::EventType Type() const { return EVENT_ACTOR_CREATED; }
		dxut::ActorId Actor() const { return mId; }

	private:
		const dxut::ActorId mId;
	};
	
//--------------------------------------------------------------------------------------

	class SpawnEvent : public dxut::IEvent
	{
	public:
		explicit SpawnEvent(float x, float y);

		dxut::EventType Type() const { return EVENT_SPAWN_ACTOR; }
		float X() const { return mX; }
		float Y() const { return mY; }

	private:
		const float mX, mY;
	};

};