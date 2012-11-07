
#include "../Application.h"
#include "../Process/Process.h"
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

	LogicBase::LogicBase()
		: mProcessManager(new ProcessManager()),
		  mInitialized(false),
		  mPaused(false)
	{
	}

//--------------------------------------------------------------------------------------

	void LogicBase::Initialize()
	{
		mInitialized = true;
	}
	
//--------------------------------------------------------------------------------------

	void LogicBase::Update(double time, float elapsedTime)
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

	std::shared_ptr<Actor> LogicBase::GetActor(const ActorId id) const
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

	void LogicBase::AddActor(std::shared_ptr<Actor> actor)
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

	void LogicBase::AddView(std::shared_ptr<IView> view)
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

	std::shared_ptr<IHumanView> LogicBase::HumanView() const
	{
		using namespace boost::lambda;

		std::shared_ptr<IView> view = *std::find_if(mViewList.begin(), mViewList.end(), bind(&IView::Type, *_1) == VIEW_HUMAN);
		return std::static_pointer_cast<IHumanView>(view);
	}
	
};