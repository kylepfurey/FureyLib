
// Asynchronous Thread Object Script
// by Kyle Furey

// REQUIREMENT: UThread.h

// Include this heading to use the class
#include "UThread.h"


// CONSTRUCTOR

// Default constructor.
UThread::UThread(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Thread = FAsyncThread();

	Delegate = FThreadDelegate();

	// Thread construction should be done in blueprints through the NewThread() function.
}


// FUNCTIONS

// Requests to stop the thread.
bool UThread::Stop()
{
	bool bStopped = Thread.IsRunning();

	Thread.Stop();

	return bStopped;
}

// Starts the thread if possible.
// Returns if the thread was successfully started. 
bool UThread::Start()
{
	return Thread.Start();
}

// Returns whether this thread has started.
bool UThread::IsStarted()
{
	return Thread.IsStarted();
}

// Returns whether this thread is currently running.
bool UThread::IsRunning()
{
	return Thread.IsRunning();
}

// Returns whether this thread successfully completed without being stopped.
bool UThread::IsCompleted()
{
	return Thread.IsCompleted();
}

// Returns whether this thread was stopped.
bool UThread::IsStopped()
{
	return Thread.IsStopped();
}

// Returns the thread's underlying delegate.
FThreadDelegate& UThread::GetDelegate()
{
	return Delegate;
}

// Returns the thread's name.
FName UThread::GetName()
{
	return Thread.GetName();
}

// Runs the given delegate on a separate asynchronous thread.
UThread* UThread::NewThread(const FThreadDelegate& Event, FName Name, bool bStart)
{
	UThread* NewThread = NewObject<UThread>();

	NewThread->Delegate = Event;

	NewThread->Thread = FAsyncThread(LAMBDA(= )
	{
		if (NewThread != nullptr)
		{
			NewThread->Delegate.ExecuteIfBound();
		}
	},
		Name, false);

	if (bStart)
	{
		NewThread->Thread.Start();
	}

	return NewThread;
}

// Returns the number of logical processors on this device.
int32 UThread::NumberOfProcessors()
{
	return FPlatformMisc::NumberOfCoresIncludingHyperthreads();
}
