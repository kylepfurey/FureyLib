// .h
// Client Player State Script
// by Kyle Furey

// REQUIREMENTS: OnlineSubsystem, ServerState.h, ClientState.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Networking/Server/ServerState.h"
#include "ClientState.generated.h"

// Include this heading to use the class
// #include "Networking/Client/ClientState.h"

/** Represents a client's player state where a client's data can be stored and shared between other clients. */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API AClientState : public APlayerState
{
	GENERATED_BODY()

protected:

	// SINGLETON

	/** A singleton reference to the client player state. */
	static AClientState* Instance;


	// CLIENT

	/** The name of this client. */
	UPROPERTY(ReplicatedUsing = OnRep_ClientName, BlueprintReadOnly, BlueprintGetter = "GetClientName", Category = "Client")
	FName ClientName = TEXT("None");


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Determines what variables can be replicated across the network. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Called when this actor is destroyed. */
	virtual void BeginDestroy() override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	AClientState();

	/** Object initializer constructor. */
	AClientState(const FObjectInitializer& ObjectInitializer);


	// SINGLETON

	/** Returns a reference reference to the client player state. */
	static AClientState* GetInstance();


	// CLIENT

	/** Returns this client state's client if this game instance owns the client or is the server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual AClient* GetClient();

	/** Returns whether the given client owns this client state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual bool IsMyClient(AClient* _Owner);


	// EVENTS

	/** Automatically called when this client's names changes. */
	UFUNCTION(BlueprintNativeEvent, Category = "Client")
	void OnClientNameChanged(FName OldName, FName NewName);
	virtual void OnClientNameChanged_Implementation(FName OldName, FName NewName);


	// GETTERS

	/** Returns the name of this client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual FName GetClientName();


	// SETTERS

	/** Sets the name of this client across the network. */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Client")
	void SetClientName(AClient* _Owner, FName _ClientName);
	virtual void SetClientName_Implementation(AClient* _Owner, FName _ClientName);

	/** Automatically called when this client's name is replicated. */
	UFUNCTION(BlueprintNativeEvent, Category = "Client")
	void OnRep_ClientName();
	virtual void OnRep_ClientName_Implementation();
};
