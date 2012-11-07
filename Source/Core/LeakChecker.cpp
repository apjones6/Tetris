
#include "../DXUT/DXUT.h"
#include "LeakChecker.h"

namespace dxut
{

	LeakChecker::LeakChecker()
	{
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	}
	
//--------------------------------------------------------------------------------------

	LeakChecker::~LeakChecker()
	{
		_CrtDumpMemoryLeaks();
	};

};