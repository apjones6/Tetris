
#pragma once

#include "Core/LeakChecker.h"
#include "DXUT/DXUT.h"

#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

namespace dxut
{
	
	class EventManager;
	class LogicBase;

//--------------------------------------------------------------------------------------

	class ApplicationBase : private boost::noncopyable
	{
	public:
		static HRESULT CALLBACK OnCreateDevice(ID3D10Device* pd3dDevice, const DXGI_SURFACE_DESC* pBufferSurfaceDesc, void* pUserContext);
		static void    CALLBACK OnDestroyDevice(void* pUserContext);
		static void    CALLBACK OnRender(ID3D10Device* pd3dDevice, double time, float elapsedTime, void *pUserContext);
		static void    CALLBACK OnUpdate(double time, float elapsedTime, void* pUserContext);
		static LRESULT CALLBACK OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

	protected:
		explicit ApplicationBase(std::shared_ptr<LogicBase> logic, std::shared_ptr<EventManager> eventManager);
		explicit ApplicationBase(std::shared_ptr<LogicBase> logic);

	public:
		virtual ~ApplicationBase() { }

		void Initialize(const std::wstring& title, bool windowed = true, int width = 800, int height = 600);
		virtual void Kill() { }
		int  Run();

		LONG Height() const { return DXUTGetWindowHeight(); }
		LONG Width() const { return DXUTGetWindowWidth(); }

		std::shared_ptr<EventManager> Events() { return mEventManager; }
		std::shared_ptr<LogicBase> Logic() { return mLogic; }

	protected:
		virtual void InitializeViews();

	private:
		std::shared_ptr<EventManager> mEventManager;
		std::shared_ptr<LogicBase> mLogic;

#if defined(DEBUG) | defined(_DEBUG)
		static LeakChecker leakChecker;
#endif
	};
	
//--------------------------------------------------------------------------------------

	extern std::shared_ptr<ApplicationBase> gApp;

};