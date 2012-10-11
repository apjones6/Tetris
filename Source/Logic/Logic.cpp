
#include "../Application.h"
#include "../Process/GameProcesses.h"
#include "GameEvents.h"
#include "Logic.h"
#include "Manager.h"

#include <algorithm>

#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

namespace dxut
{
	
	Actor::Actor(const ActorId id, const ActorType type, float x, float y)
		: mId(id),
		  mType(type),
		  mX(x),
		  mY(y)
	{
	}
	
//--------------------------------------------------------------------------------------

	Actor::Actor(const ActorId id, const ActorType type)
		: mId(id),
		  mType(type),
		  mX(0),
		  mY(0)
	{
	}
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

	BaseLogic::BaseLogic()
		: mProcessManager(new ProcessManager()),
		  mInitialized(false),
		  mPaused(false)
	{
	}

//--------------------------------------------------------------------------------------

	void BaseLogic::Initialize()
	{
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
		mProcessManager->Attach(processes[0]);

		mInitialized = true;
	}
	
//--------------------------------------------------------------------------------------

	void BaseLogic::Update(double time, float elapsedTime)
	{
		assert(mInitialized);
		assert(!mPaused);

		// Update processes
		mProcessManager->Update(elapsedTime);

		// Update views
		BOOST_FOREACH (std::shared_ptr<IView> view, mViewList)
		{
			view->Update(time, elapsedTime);
		}
	}

//--------------------------------------------------------------------------------------

	std::shared_ptr<Actor> BaseLogic::GetActor(const ActorId id) const
	{
		assert(mInitialized);

		// Use find to ensure we don't insert a default constructed pointer into map
		const ActorMap::const_iterator i = mActorMap.find(id);
		if (i != mActorMap.end())
		{
			return i->second;
		}
		else
		{
			return NULL;
		}
	}

//--------------------------------------------------------------------------------------

	void BaseLogic::AddActor(std::shared_ptr<Actor> actor)
	{
		assert(mInitialized);
		assert(mActorMap.count(actor->Id()) == 0);
		assert(!mPaused);

		// Insert
		mActorMap[actor->Id()] = actor;

		// Notify
		EventPtr e(new ActorEvent(actor->Id()));
		gApp->Events()->Dispatch(e);
	}
	
//--------------------------------------------------------------------------------------

	void BaseLogic::AddView(std::shared_ptr<IView> view)
	{
		assert(mInitialized);

		// Ensure not duplicate
		const ViewList::const_iterator i = std::find(mViewList.begin(), mViewList.end(), view);
		if (i != mViewList.end())
			return;

		// Insert
		mViewList.push_back(view);
	}
	
//--------------------------------------------------------------------------------------

	std::shared_ptr<IHumanView> BaseLogic::HumanView() const
	{
		using namespace boost::lambda;

		std::shared_ptr<IView> view = *std::find_if(mViewList.begin(), mViewList.end(), bind(&IView::Type, *_1) == VIEW_HUMAN);
		return std::static_pointer_cast<IHumanView>(view);
	}
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

	bool LogicListener::Handle(EventPtr e)
	{
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