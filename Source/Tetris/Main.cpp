
#include "Application.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace dxut;
	
	// Initialize application instance
	gApp = std::shared_ptr<ApplicationBase>(new tetris::Application);

	// Run
	gApp->Initialize(L"Apjones Tetris");
	int exit = gApp->Run();

	// Kill
	gApp->Kill();
	gApp.reset();

	// Exit
	return exit;
}