
// Asynchronous Thread Script
// by Kyle Furey

// REQUIREMENT: AsyncThread.cpp

// REFERENCE: https://forums.unrealengine.com/t/multithreading-and-performance-in-unreal/1216417

#pragma once
#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "HAL/Runnable.h"
#include "HAL/PlatformMisc.h"

// Include this heading to use the class
// #include "Async Thread/AsyncThread.h"

// Creates a lambda expression with the given captures and code.
#define LAMBDA(...) [__VA_ARGS__] () mutable -> void

/**
* Represents a single-use asynchronous thread.
* Can be supplied a function to complete work on a separate thread.
*/
class MYGAME_API FAsyncThread : public FRunnable
{
protected:

	// VARIABLES

	/** The underlying thread. */
	FRunnableThread* Thread = nullptr;

	/** This thread's cancellation token. */
	bool bShutdown = false;

	/** A function to the work this thread will complete. */
	TFunction<void()> Delegate = TFunction<void()>();

	/** The name of this thread. */
	FName ThreadName = "New Thread";

	/** Whether or not this thread has started. */
	bool bStarted = false;

	/** Whether or not this thread is currently running. */
	bool bRunning = false;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	FAsyncThread();

	/** Function and name constructor. */
	FAsyncThread(TFunction<void()> Event, FName Name = "New Thread", bool bStart = true);

	/** Destructor. */
	virtual ~FAsyncThread();


	// FUNCTIONS

	/**
	* Automatically called.
	* Called when the thread is initialized.
	*/
	virtual bool Init() override;

	/**
	* Runs the thread's work on a separate thread.
	* Automatically called.
	*/
	virtual uint32 Run() override;

	/**
	* Called when the thread completes its work.
	* Automatically called.
	*/
	virtual void Exit() override;

	/** Requests to stop the thread. */
	virtual void Stop() override;

	/**
	* Starts the thread if possible.
	* Returns if the thread was successfully started.
	*/
	virtual bool Start();

	/** Returns whether this thread has started. */
	virtual bool IsStarted();

	/** Returns whether this thread is currently running. */
	virtual bool IsRunning();

	/** Returns whether this thread successfully completed without being stopped. */
	virtual bool IsCompleted();

	/** Returns whether this thread was stopped. */
	virtual bool IsStopped();

	/** Returns the underlying thread. */
	virtual FRunnableThread* GetThread();

	/** Returns the thread's underlying function. */
	virtual TFunction<void()> GetFunction();

	/** Returns the thread's name. */
	virtual FName GetName();

	/** Returns the number of logical processors on this device. */
	static int32 NumberOfProcessors();
};
