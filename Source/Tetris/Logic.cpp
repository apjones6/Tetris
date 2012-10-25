
#include "../Application.h"
#include "../Logic/GameEvents.h"
#include "../Logic/Manager.h"
#include "../Process/GameProcesses.h"
#include "Logic.h"

#include <algorithm>

#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

namespace tetris
{
	
	Logic::Logic()
		: dxut::LogicBase()
	{
	}

//--------------------------------------------------------------------------------------

	void Logic::Initialize()
	{
		using namespace dxut;

		// Base initialization (sets initialized true, so possibly should be last)
		LogicBase::Initialize();

		ListenerPtr listener(new LogicListener);
		gApp->Events()->AddListener(listener, EVENT_SPAWN_ACTOR);

		std::shared_ptr<Process> processes[9];
		float offset = -0.4f;

		for (int i = 0; i < 9; ++i)
		{
			const ActorId id = NextActorId();

			// Create proccesses
			std::shared_ptr<Process> spawn(new SpawnProcess(offset, offset, id));
			std::shared_ptr<Process> delay(new DelayProcess(1.0, spawn));
			processes[i] = delay;

			// Set delay to follow last spawn
			if (i > 0)
			{
				processes[i - 1]->Next()->SetNext(delay);
			}

			offset += 0.1f;
		}

		// Attach first process to process manager
		Processes()->Attach(processes[0]);
	}
	
//--------------------------------------------------------------------------------------

	void Logic::Update(double time, float elapsedTime)
	{
		dxut::LogicBase::Update(time, elapsedTime);
	}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

	bool LogicListener::Handle(dxut::EventPtr e)
	{
		using namespace dxut;

		// Escape if paused
		if (gApp->Logic()->IsPaused())
			return false;

		// Handle known events
		if (e->Type() == EVENT_SPAWN_ACTOR)
		{
			const SpawnEvent& spawn = static_cast<SpawnEvent&>(*e);
			
			const ActorId id = gApp->Logic()->NextActorId();

			std::shared_ptr<Actor> actor(new Actor(id, ACTOR_TYPE_TRIANGLE, spawn.X(), spawn.Y()));
			gApp->Logic()->AddActor(actor);

			return true;
		}

		// Ignore other events
		return false;
	}

};