
#include "Application.h"
#include "Core/Message.h"
#include "Logic/Logic.h"
#include "Logic/Manager.h"
#include "Views/HumanView.h"

#include <boost/foreach.hpp>

namespace dxut
{
	
	std::shared_ptr<Application> gApp = NULL;

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	HRESULT CALLBACK Application::OnCreateDevice(ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext)
	{
		BOOST_FOREACH (std::shared_ptr<IView> view, gApp->Logic()->Views())
		{
			view->Initialize();
		}

		return S_OK;
	}
	
//--------------------------------------------------------------------------------------

	void CALLBACK Application::OnDestroyDevice(void* pUserContext)
	{
		BOOST_FOREACH (std::shared_ptr<IView> view, gApp->Logic()->Views())
		{
			view->Kill();
		}
	}

//--------------------------------------------------------------------------------------

	void CALLBACK Application::OnRender(ID3D10Device* pd3dDevice, double time, float elapsedTime, void *pUserContext)
	{
		gApp->Logic()->HumanView()->Render(pd3dDevice);
	}
	
//--------------------------------------------------------------------------------------

	void CALLBACK Application::OnUpdate(double time, float elapsedTime, void* pUserContext)
	{
		// Escape if paused
		if (gApp->mLogic->IsPaused())
			return;
		
		gApp->mLogic->Update(time, elapsedTime);
	}
	
//--------------------------------------------------------------------------------------

	LRESULT CALLBACK Application::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
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
	
	Application::Application(std::shared_ptr<EventManager> eventManager, std::shared_ptr<BaseLogic> logic)
		: mEventManager(eventManager),
		  mLogic(logic)
	{
	}

//--------------------------------------------------------------------------------------

	Application::Application()
		: mEventManager(new EventManager),
		  mLogic(new BaseLogic)
	{
	}

//--------------------------------------------------------------------------------------

	void Application::Initialize(const std::wstring& title, bool windowed, int width, int height)
	{
		HRESULT hr;

		// Initialize event manager
		RegisterEvents();

		// Initialize logic
		mLogic->Initialize();

		// Initialize views
		std::shared_ptr<IView> view(new HumanView);
		mLogic->AddView(view);

		// Register DXUT Callbacks
		DXUTSetCallbackD3D10DeviceCreated(Application::OnCreateDevice);
		DXUTSetCallbackD3D10DeviceDestroyed(Application::OnDestroyDevice);
		DXUTSetCallbackD3D10FrameRender(Application::OnRender);
		DXUTSetCallbackFrameMove(Application::OnUpdate);
		DXUTSetCallbackMsgProc(Application::OnMsgProc);

		// Initialize Window and DirectX
		V(DXUTCreateWindow(title.c_str()));
		V(DXUTCreateDevice(windowed, width, height));
	}
	
//--------------------------------------------------------------------------------------

	int Application::Run()
	{
		HRESULT hr;

		// Execute Main Loop
		V(DXUTMainLoop());

		DXUTShutdown();

		// Return exit code
		return DXUTGetExitCode();
	}
	
};