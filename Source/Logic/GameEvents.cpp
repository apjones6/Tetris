
#include "GameEvents.h"

namespace dxut
{
	
	ActorEvent::ActorEvent(const ActorId id)
		: mId(id)
	{
	}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	SpawnEvent::SpawnEvent(float x, float y)
		: mX(x),
		  mY(y)
	{
	}

};