
#pragma once

#include "../Input/Input.h"
#include "../Logic/Listener.h"
#include "Scene.h"
#include "View.h"

namespace dxut
{
	
	class HumanView : public IHumanView
	{
	public:
		explicit HumanView();

		ViewType Type() const { return VIEW_HUMAN; }

		void Initialize();
		void Update(double time, float elapsedTime);
		void Render(ID3D10Device* pd3dDevice);
		void Kill();

		LRESULT OnMsgProc(const Message& message);

		void AddView(std::shared_ptr<IViewElement> view);

		std::shared_ptr<Scene> RootScene() { return mScene; }
		
	private:
		ID3D10Effect*			mFX;
		ID3D10EffectTechnique*  mTech;
		ID3D10InputLayout*		mLayout;

		std::shared_ptr<Scene> mScene;
		ViewElementList		   mElementList;

		ListenerPtr		mListener;

		std::shared_ptr<IKeyboardHandler> mKeyboardHandler;
		std::shared_ptr<IMouseHandler>	  mMouseHandler;
	};
	
//--------------------------------------------------------------------------------------

	class ViewListener : public IListener
	{
	public:
		bool Handle(EventPtr e);
	};

};