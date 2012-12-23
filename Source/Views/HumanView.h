
#pragma once

#include "View.h"

namespace dxut
{
	
	class IKeyboardHandler;
	class IMouseHandler;
	class Scene;
	
//--------------------------------------------------------------------------------------
	
	class HumanView : public IHumanView
	{
	public:
		explicit HumanView(std::shared_ptr<IKeyboardHandler> keyboardHandler, std::shared_ptr<IMouseHandler> mouseHandler);
		explicit HumanView();

		ViewType Type() const { return VIEW_HUMAN; }

		void Initialize();
		void Update(double time, float elapsedTime);
		void Render(ID3D10Device* pd3dDevice);
		void Kill();

		LRESULT OnMsgProc(const Message& message);
		
		bool Visible() const { return true; }
		void Visible(bool visible) { }

		void AddView(std::shared_ptr<IViewElement> view);
		void RemoveView(std::shared_ptr<IViewElement> view);

		std::shared_ptr<Scene> RootScene() { return mScene; }
		
	private:
		ID3D10Effect*			mFX;
		ID3D10EffectTechnique*  mTech;
		ID3D10InputLayout*		mLayout;

		std::shared_ptr<Scene> mScene;
		ViewElementList		   mElementList;

		std::shared_ptr<IKeyboardHandler> mKeyboardHandler;
		std::shared_ptr<IMouseHandler>	  mMouseHandler;
	};
	
};