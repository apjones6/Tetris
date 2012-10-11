
#pragma once

#include "Core/LeakChecker.h"
#include "DXUT/DXUT.h"

#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

namespace dxut
{
	
	class EventManager;
	class BaseLogic;

//--------------------------------------------------------------------------------------

	class Application : private boost::noncopyable
	{
	public:
		static HRESULT CALLBACK OnCreateDevice(ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext);
		static void    CALLBACK OnDestroyDevice(void* pUserContext);
		static void    CALLBACK OnRender(ID3D10Device* pd3dDevice, double time, float elapsedTime, void *pUserContext);
		static void    CALLBACK OnUpdate(double time, float elapsedTime, void* pUserContext);
		static LRESULT CALLBACK OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

	public:
		explicit Application();
		virtual ~Application() { }

		void Initialize(const std::wstring& title, bool windowed = true, int width = 800, int height = 600);
		int  Run();

		LONG Height() const { return DXUTGetWindowHeight(); }
		LONG Width() const { return DXUTGetWindowWidth(); }

		std::shared_ptr<EventManager> Events() { return mEventManager; }
		std::shared_ptr<BaseLogic> Logic() { return mLogic; }

	protected:
		virtual void RegisterEvents();

	private:
		std::shared_ptr<EventManager> mEventManager;
		std::shared_ptr<BaseLogic> mLogic;

#if defined(DEBUG) | defined(_DEBUG)
		static LeakChecker leakChecker;
#endif
	};
	
//--------------------------------------------------------------------------------------

	extern std::shared_ptr<Application> gApp;

};