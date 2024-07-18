
// Static Print Function Script
// by Kyle Furey

#pragma once
#include <stdio.h>

// Include this heading to use the library
#include "print.h"

// Prints a message to the console
#define PRINT(log) printf(log); printf("\n");

// Prints a message to the console
static void print(char* log)
{
	printf(log);
	
	printf("\n");
}
