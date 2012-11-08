
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

	/**
	 * The recognized types of view, such as Human, AI or Remote views.
	 */
	enum ViewType
	{
		VIEW_HUMAN,
		VIEW_AI
	};
	
//--------------------------------------------------------------------------------------

	/**
	 * An element of a view, which could be a user interface control, a 2D or 3D scene graph.
	 */
	class IViewElement
	{
	public:
		virtual ~IViewElement() { }

		virtual void Update(double time, float elapsedTime) = 0;
		virtual void Render(ID3D10Device* pd3dDevice) = 0;
		virtual void Kill() = 0;

		virtual LRESULT OnMsgProc(const Message& message) = 0;
	};
	
//--------------------------------------------------------------------------------------

	/**
	 * A root view, such as a Human, AI or Remote view, which parses input and acts on the logic.
	 */
	class IView : public IViewElement
	{
	public:
		virtual ViewType Type() const = 0;

		virtual void Initialize() = 0;
	};
	
//--------------------------------------------------------------------------------------

	/**
	 * A local human view, which handles input such as keyboard and mouse, and outputs display and audio content.
	 */
	class IHumanView : public IView
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