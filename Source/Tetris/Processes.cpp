
#include "../Application.h"
#include "Logic.h"
#include "Processes.h"

namespace tetris
{
	
	DelayProcess::DelayProcess(double time)
		: mTimeRemaining(time)
	{
	}
	
//--------------------------------------------------------------------------------------

	DelayProcess::DelayProcess(double time, std::shared_ptr<Process> next)
		: mTimeRemaining(time)
	{
		SetNext(next);
	}
	
//--------------------------------------------------------------------------------------

	void DelayProcess::Update(float elapsedTime)
	{
		Process::Update(elapsedTime);

		// Kill when time remaining reaches zero
		if ((mTimeRemaining -= elapsedTime) <= 0.0)
		{
			Kill();
		}
	}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	SpawnProcess::SpawnProcess(float x, float y, const dxut::ActorId id)
		: mX(x),
		  mY(y),
		  mId(id)
	{
	}
	
//--------------------------------------------------------------------------------------

	void SpawnProcess::Update(float elapsedTime)
	{
		using namespace dxut;

		Process::Update(elapsedTime);

		// Spawn immediately
		std::shared_ptr<Actor> actor(new Actor(mId, ACTOR_TYPE_SQUARE, mX, mY));
		gApp->Logic()->AddActor(actor);

		// Kill
		Kill();
	}

};