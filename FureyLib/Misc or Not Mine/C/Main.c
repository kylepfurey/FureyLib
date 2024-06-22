
// Program Main Entry Point Script

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <crtdbg.h>

// Entry point of the program
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);

	printf("Hello, Dinner!\n");

	// New code here

	_CrtDumpMemoryLeaks();
	return 0;
}
