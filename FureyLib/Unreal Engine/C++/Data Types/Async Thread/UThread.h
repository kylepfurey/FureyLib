
// Asynchronous Thread Object Script
// by Kyle Furey

// REQUIREMENTS: AsyncThread.h, UThread.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Async Thread/AsyncThread.h"
#include "UThread.generated.h"

// Include this heading to use the class
// #include "Async Thread/UThread.h"

// Delegate declaration.
DECLARE_DYNAMIC_DELEGATE(FThreadDelegate);

/**
 * Runs a delegate on a separate thread.
 * Construct with the NewThread() function.
 * Used exclusively for blueprint support.
 */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UThread : public UObject
{
	GENERATED_BODY()

protected:

	/** The underlying thread. */
	FAsyncThread Thread = FAsyncThread();

	/** The underlying delegate this UThread stores. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetDelegate", meta = (ExposeOnSpawn), Category = "Multithreading")
	FThreadDelegate Delegate = FThreadDelegate();

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UThread();

	/** Object initializer constructor. */
	UThread(const FObjectInitializer& ObjectInitializer);


	// FUNCTIONS

	/**
	* Requests to stop the thread.
	* Returns if the thread was successfully stopped.
	*/
	UFUNCTION(BlueprintCallable, Category = "Multithreading")
	virtual bool Stop();

	/**
	* Starts the thread if possible.
	* Returns if the thread was successfully started.
	*/
	UFUNCTION(BlueprintCallable, Category = "Multithreading")
	virtual bool Start();

	/** Returns whether this thread has started. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	virtual bool IsStarted();

	/** Returns whether this thread is currently running. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	virtual bool IsRunning();

	/** Returns whether this thread successfully completed without being stopped. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	virtual bool IsCompleted();

	/** Returns whether this thread was stopped. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	virtual bool IsStopped();

	/** Returns the thread's underlying delegate. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	virtual FThreadDelegate& GetDelegate();

	/** Returns the thread's name. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	virtual FName GetName();

	/** Runs the given delegate on a separate asynchronous thread. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "Multithreading")
	static UThread* NewThread(const FThreadDelegate& Event, FName Name = "New Thread", bool bStart = true);

	/** Returns the number of logical processors on this device. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multithreading")
	static int32 NumberOfProcessors();
};
