
#include "../Application.h"
#include "../Logic/GameEvents.h"
#include "../Views/QuadView.h"
#include "../Views/TriangleView.h"
#include "Logic.h"
#include "View.h"

namespace tetris
{
	
	bool ViewListener::Handle(dxut::EventPtr e)
	{
		using namespace dxut;

		if (e->Type() == EVENT_ACTOR_CREATED)
		{
			const ActorEvent& actorEvt = static_cast<ActorEvent&>(*e);
			const std::shared_ptr<Actor> actor(gApp->Logic()->GetActor(actorEvt.Actor()));
			
			std::shared_ptr<SceneNode> node;
			if (actor->Type() == ACTOR_TYPE_SQUARE)
			{
				node.reset(new Quad(actor->Id(), actor->X(), actor->Y(), 1.0f, 1.0f, actor->Id() % 2 == 0 ? RED : BLUE));
			}
			else
			{
				node.reset(new Triangle(actor->Id(), actor->X(), actor->Y(), 0.2f, 0.2f));
			}

			gApp->Logic()->HumanView()->RootScene()->AddNode(node);
			return true;
		}

		return false;
	}

};