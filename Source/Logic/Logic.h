
#pragma once

#include "../Views/View.h"

#include <map>

namespace dxut
{
	
	typedef unsigned int ActorId;
	typedef unsigned int ActorType;

//--------------------------------------------------------------------------------------
	
	class Actor
	{
	public:
		explicit Actor(const ActorId id, const ActorType type, float x, float y);
		explicit Actor(const ActorId id, const ActorType type);
		virtual ~Actor() { };

		ActorId   Id() const { return mId; }
		ActorType Type() const { return mType; }

		float     X() const { return mX; }
		float     Y() const { return mY; }

	private:
		const ActorId mId;
		const ActorType mType;
		float mX, mY;
	};

//--------------------------------------------------------------------------------------
	
	typedef std::map<ActorId, std::shared_ptr<Actor>> ActorMap;

//--------------------------------------------------------------------------------------
	
	class ProcessManager;

//--------------------------------------------------------------------------------------

	class LogicBase
	{
	protected:
		explicit LogicBase();

	public:
		virtual ~LogicBase() { }

		virtual void Initialize();
		virtual void Update(double time, float elapsedTime);

		std::shared_ptr<ProcessManager> Processes() { return mProcessManager; }

		ActorId NextActorId() { return ++mNextActorId; }

		std::shared_ptr<Actor> GetActor(const ActorId id) const;
		virtual void AddActor(std::shared_ptr<Actor> actor);

		void AddView(std::shared_ptr<IView> view);
		const ViewList& Views() const { return mViewList; }

		std::shared_ptr<IHumanView> HumanView() const;

		bool IsInitialized() const { return mInitialized; }
		bool IsPaused() const { return mPaused; }

		void SetPaused(bool pause) { mPaused = pause; }

	private:
		std::shared_ptr<ProcessManager> mProcessManager;

		ActorId  mNextActorId;
		ActorMap mActorMap;

		ViewList mViewList;

		bool mInitialized;
		bool mPaused;
	};
	
//--------------------------------------------------------------------------------------
	
	static void TogglePause(std::shared_ptr<LogicBase> logic)
	{
		const bool paused = logic->IsPaused();
		logic->SetPaused(!paused);
	}

};