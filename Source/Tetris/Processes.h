
#pragma once

#include "../Logic/Logic.h"
#include "../Process/Process.h"

namespace tetris
{
	
	class DelayProcess : public dxut::Process
	{
	public:
		explicit DelayProcess(double time);
		explicit DelayProcess(double time, std::shared_ptr<Process> next);

		void Update(float elapsedTime);

	private:
		double mTimeRemaining;
	};
	
//--------------------------------------------------------------------------------------

	class SpawnProcess : public dxut::Process
	{
	public:
		explicit SpawnProcess(float x, float y, const dxut::ActorId id);

		void Update(float elapsedTime);

	private:
		const float mX, mY;
		const dxut::ActorId mId;
	};

};