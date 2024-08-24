
// Asynchronous Thread Script
// by Kyle Furey

// REQUIREMENT: AsyncThread.h

// REFERENCE: https://forums.unrealengine.com/t/multithreading-and-performance-in-unreal/1216417

// Include this heading to use the class
#include "Async Thread/AsyncThread.h"


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor.
FAsyncThread::FAsyncThread()
{
	Thread = nullptr;

	bShutdown = false;

	Delegate = nullptr;

	ThreadName = "NULL Thread";

	bStarted = false;

	bRunning = false;
}

// Function and name constructor.
FAsyncThread::FAsyncThread(TFunction<void()> Event, FName Name, bool bStart)
{
	if (bStart)
	{
		Thread = FRunnableThread::Create(this, *Name.ToString());
	}
	else
	{
		Thread = nullptr;
	}

	bShutdown = false;

	Delegate = Event;

	ThreadName = Name;

	bStarted = bStart;

	bRunning = false;
}

// Destructor.
FAsyncThread::~FAsyncThread() { }


// FUNCTIONS

// Automatically called.
// Called when the thread is initialized.
bool FAsyncThread::Init()
{
	bRunning = true;

	return true;
}

// Automatically called.
// Runs the thread's work on a separate thread.
uint32 FAsyncThread::Run()
{
	if (Delegate != nullptr)
	{
		Delegate();

		return 0;
	}
	else
	{
		return -1;
	}
}

// Automatically called.
// Called when the thread completes its work.
void FAsyncThread::Exit()
{
	bRunning = false;
}

// Requests to stop the thread.
void FAsyncThread::Stop()
{
	if (bRunning)
	{
		bShutdown = true;
	}
}

// Starts the thread if possible.
// Returns if the thread has successfully been started.
bool FAsyncThread::Start()
{
	bStarted = true;

	if (Thread == nullptr)
	{
		Thread = FRunnableThread::Create(this, *ThreadName.ToString());

		return true;
	}
	else
	{
		return false;
	}
}

// Returns whether this thread has started.
bool FAsyncThread::IsStarted()
{
	return bStarted;
}

// Returns whether this thread is currently running.
bool FAsyncThread::IsRunning()
{
	return bRunning;
}

// Returns whether this thread successfully completed without being stopped.
bool FAsyncThread::IsCompleted()
{
	return bStarted && !bRunning && !bShutdown;
}

// Returns whether this thread was stopped.
bool FAsyncThread::IsStopped()
{
	return bShutdown;
}

// Returns the underlying thread.
FRunnableThread* FAsyncThread::GetThread()
{
	return Thread;
}

// Returns the thread's underlying function.
TFunction<void()> FAsyncThread::GetFunction()
{
	return Delegate;
}

// Returns the thread's name.
FName FAsyncThread::GetName()
{
	return ThreadName;
}

// Returns the number of logical processors on this device.
int32 FAsyncThread::NumberOfProcessors()
{
	return FPlatformMisc::NumberOfCoresIncludingHyperthreads();
}

