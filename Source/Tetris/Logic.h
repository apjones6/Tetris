
#pragma once

#include "../Logic/Listener.h"
#include "../Logic/Logic.h"

namespace tetris
{
	
	const dxut::ActorType ACTOR_TYPE_SQUARE = 1;
	const dxut::ActorType ACTOR_TYPE_TRIANGLE = 2;

//--------------------------------------------------------------------------------------

	class Logic : public dxut::LogicBase
	{
	public:
		explicit Logic();

		void Initialize();
		void Update(double time, float elapsedTime);
	};
	
//--------------------------------------------------------------------------------------

	class LogicListener : public dxut::IListener
	{
	public:
		bool Handle(dxut::EventPtr e);
	};

};