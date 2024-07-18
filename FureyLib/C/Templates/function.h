
// Template Static Function Library Script
// by Kyle Furey

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Include this heading to use the library
#include "function.h"

// Example function
static void function()
{
	printf("Function called!\n");
}

// Prints a message to the console
static void print(char* log)
{
	printf(log);
	
	printf("\n");
}
