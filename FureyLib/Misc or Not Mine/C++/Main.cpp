
// Program Main Entry Point Script

#include <crtdbg.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Entry point of the program
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);

	cout << "Hello, Dinner!" << endl;

	// New code here

	_CrtDumpMemoryLeaks();
	return 0;
}
