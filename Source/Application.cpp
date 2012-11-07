
#include "Application.h"
#include "Core/Message.h"
#include "Logic/Logic.h"
#include "Logic/Manager.h"
#include "Views/HumanView.h"

#include <boost/foreach.hpp>

namespace dxut
{
	
	std::shared_ptr<ApplicationBase> gApp = NULL;

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	HRESULT CALLBACK ApplicationBase::OnCreateDevice(ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext)
	{
		BOOST_FOREACH (std::shared_ptr<IView> view, gApp->Logic()->Views())
		{
			view->Initialize();
		}

		return S_OK;
	}
	
//--------------------------------------------------------------------------------------

	void CALLBACK ApplicationBase::OnDestroyDevice(void* pUserContext)
	{
		BOOST_FOREACH (std::shared_ptr<IView> view, gApp->Logic()->Views())
		{
			view->Kill();
		}
	}

//--------------------------------------------------------------------------------------

	void CALLBACK ApplicationBase::OnRender(ID3D10Device* pd3dDevice, double time, float elapsedTime, void *pUserContext)
	{
		gApp->Logic()->HumanView()->Render(pd3dDevice);
	}
	
//--------------------------------------------------------------------------------------

	void CALLBACK ApplicationBase::OnUpdate(double time, float elapsedTime, void* pUserContext)
	{
		// Escape if paused
		if (gApp->mLogic->IsPaused())
			return;
		
		gApp->mLogic->Update(time, elapsedTime);
	}
	
//--------------------------------------------------------------------------------------

	LRESULT CALLBACK ApplicationBase::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
	{
		LRESULT result = NULL;

		switch (uMsg)
		{
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_CHAR:
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
				{
					Message message(hWnd, uMsg, wParam, lParam);

					// Iterate in reverse order (front to back)
					BOOST_REVERSE_FOREACH (std::shared_ptr<IView> view, gApp->Logic()->Views())
					{
						if (view->OnMsgProc(message))
						{
							result = true;
							break;
						}
					}
				}

				break;
		}

		return result;
	}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	ApplicationBase::ApplicationBase(std::shared_ptr<LogicBase> logic, std::shared_ptr<EventManager> eventManager)
		: mEventManager(eventManager),
		  mLogic(logic)
	{
	}

//--------------------------------------------------------------------------------------
	
	ApplicationBase::ApplicationBase(std::shared_ptr<LogicBase> logic)
		: mEventManager(new EventManager),
		  mLogic(logic)
	{
	}

//--------------------------------------------------------------------------------------

	void ApplicationBase::Initialize(const std::wstring& title, bool windowed, int width, int height)
	{
		HRESULT hr;

		// Initialize logic
		mLogic->Initialize();

		// Initialize views
		InitializeViews();

		// Register DXUT Callbacks
		DXUTSetCallbackD3D10DeviceCreated(ApplicationBase::OnCreateDevice);
		DXUTSetCallbackD3D10DeviceDestroyed(ApplicationBase::OnDestroyDevice);
		DXUTSetCallbackD3D10FrameRender(ApplicationBase::OnRender);
		DXUTSetCallbackFrameMove(ApplicationBase::OnUpdate);
		DXUTSetCallbackMsgProc(ApplicationBase::OnMsgProc);

		// Initialize Window and DirectX
		V(DXUTCreateWindow(title.c_str()));
		V(DXUTCreateDevice(windowed, width, height));
	}
	
//--------------------------------------------------------------------------------------

	int ApplicationBase::Run()
	{
		HRESULT hr;

		// Execute Main Loop
		V(DXUTMainLoop());

		DXUTShutdown();

		// Return exit code
		return DXUTGetExitCode();
	}
	
//--------------------------------------------------------------------------------------

	void ApplicationBase::InitializeViews()
	{
		std::shared_ptr<IView> view(new HumanView);
		mLogic->AddView(view);
	}
	
};