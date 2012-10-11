
#pragma once

#include "../Logic/Logic.h"
#include "Process.h"

namespace dxut
{
	
	class DelayProcess : public Process
	{
	public:
		explicit DelayProcess(double time);
		explicit DelayProcess(double time, std::shared_ptr<Process> next);

		void Update(float elapsedTime);

	private:
		double mTimeRemaining;
	};
	
//--------------------------------------------------------------------------------------

	class SpawnProcess : public Process
	{
	public:
		explicit SpawnProcess(float x, float y, const ActorId id);

		void Update(float elapsedTime);

	private:
		const float mX, mY;
		const ActorId mId;
	};

};