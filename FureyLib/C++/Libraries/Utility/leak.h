
// Leak Detection Macros Script
// by Kyle Furey

#pragma once
#include <crtdbg.h>

// Include this heading to use the library
#include "leak.h"

// •  Tracks allocated memory for memory leaks.
// •  Dumps them into the output log when DUMP_LEAKS is called.
// •  Call this at the beginning of the program.
#define FIND_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); {

// •  Tracks allocated memory for memory leaks.
// •  Aborts the program when one is found after DUMP_LEAKS is called.
// •  Call this at the beginning of the program.
#define THROW_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW); {

// •  Dumps the located memory leaks into the output log.
// •  Call this before the end of the program.
#define DUMP_LEAKS } _CrtDumpMemoryLeaks();

// •  Shorthand for "DUMP_LEAKS; return 0;"
// •  Dumps the located memory leaks into the output log and ends the program.
// •  Call this at the end of the program.
#define RETURN DUMP_LEAKS; return 0;
