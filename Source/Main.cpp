
#include "Application.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace dxut;
	
	// Initialize application instance
	gApp = std::shared_ptr<Application>(new Application);

	// Run
	gApp->Initialize(L"DXUT Test Application");
	int exit = gApp->Run();

	// Kill
	gApp.reset();

	// Exit
	return exit;
}