// .clr.cpp
// Program Main Entry Point Script

#include "pch.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace Application
{
	/** The class representing the program that the application is running on. */
	static public ref class Program
	{
	public:

		/** Entry point of the program. */
		static int Main(array<String^>^ args)
		{
			Console::WriteLine("Hello, Dinner!");

			// New code here

			return 0;
		}
	};
}

/** Stores arguments and runs Program::Main(). */
int main(int argc, char* argv[])
{
	array<String^>^ args = gcnew array<String^>(argc);
	for (int i = 0; i < argc; ++i)
	{
		args[i] = gcnew String(argv[i]);
	}
	return Application::Program::Main(args);
}
