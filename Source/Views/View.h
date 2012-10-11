
#pragma once

#include <D3D10_1.h>
#include <D3DX10math.h>

#include <list>
#include <memory>

namespace dxut
{
	
	class Scene;
	struct Message;
	
//--------------------------------------------------------------------------------------

	enum ViewType
	{
		VIEW_HUMAN,
		VIEW_AI
	};
	
//--------------------------------------------------------------------------------------

	class IRenderView
	{
	public:
		virtual void Render(ID3D10Device* pd3dDevice) = 0;
	};

//--------------------------------------------------------------------------------------

	class IViewElement : public IRenderView
	{
	public:
		virtual ~IViewElement() { }

		virtual void Update(double time, float elapsedTime) = 0;
		virtual void Kill() = 0;
	};
	
//--------------------------------------------------------------------------------------

	class IView
	{
	public:
		virtual ~IView() { }

		virtual ViewType Type() const = 0;

		virtual void Initialize() = 0;
		virtual void Update(double time, float elapsedTime) = 0;
		virtual void Kill() = 0;

		virtual LRESULT OnMsgProc(const Message& message) = 0;
	};
	
//--------------------------------------------------------------------------------------

	class IHumanView : public IView, public IRenderView
	{
	public:
		virtual void AddView(std::shared_ptr<IViewElement> view) = 0;

		virtual std::shared_ptr<Scene> RootScene() = 0;
	};

//--------------------------------------------------------------------------------------

	typedef std::list<std::shared_ptr<IViewElement>> ViewElementList;
	typedef std::list<std::shared_ptr<IView>> ViewList;
	
//--------------------------------------------------------------------------------------

	//TODO: Let this be encapsulated within each view element
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR   col;
	};
	
//--------------------------------------------------------------------------------------

	const D3DXCOLOR BLACK (0.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR RED   (1.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR BLUE  (0.0f, 0.0f, 1.0f, 1.0f);
	const D3DXCOLOR GREEN (0.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR PURPLE(1.0f, 0.0f, 1.0f, 1.0f);
	
};