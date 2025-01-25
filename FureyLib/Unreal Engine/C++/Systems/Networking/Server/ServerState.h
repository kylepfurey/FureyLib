// .h
// Server Game State Base Script
// by Kyle Furey

// REQUIREMENTS: OnlineSubsystem, Client.h, ServerState.cpp, ClientState.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Networking/Client/Client.h"
#include "ServerState.generated.h"

// Include this heading to use the class
// #include "Networking/Server/ServerState.h"

/** Represents a game state base where game data can be stored and updated by the server while still being accessible by all connected clients. */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API AServerState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	// SINGLETON

	/** A singleton reference to the server game state base. */
	static AServerState* Instance;


	// SERVER

	/** The maximum number of clients that can connect to this server. */
	UPROPERTY(Replicated, BlueprintReadOnly, BlueprintGetter = "GetMaxClients", Category = "Server")
	int64 MaxClients = 0;

	/** The name of this server. */
	UPROPERTY(Replicated, BlueprintReadOnly, BlueprintGetter = "GetServerName", Category = "Server")
	FName ServerName = TEXT("None");


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Determines what variables can be replicated across the network. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Called when this actor is destroyed. */
	virtual void BeginDestroy() override;

public:

	// SERVER

	/** The total number of connected clients. */
	UPROPERTY(Replicated, BlueprintReadOnly, BlueprintGetter = "GetTotalClients", Category = "Server")
	int64 TotalClients = 0;


	// CONSTRUCTORS

	/** Default constructor. */
	AServerState();

	/** Object initializer constructor. */
	AServerState(const FObjectInitializer& ObjectInitializer);


	// SINGLETON

	/** Returns a reference to the server game state base. */
	static AServerState* GetInstance();


	// SERVER

	/** Returns the server if this game instance has authority. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual AServer* GetServer();


	// EVENTS

	/** Automatically called when a new client connects to the server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Server")
	void OnClientConnected(AClientState* ClientState);
	virtual void OnClientConnected_Implementation(AClientState* ClientState);

	/** Automatically called when a client disconnects from the server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Server")
	void OnClientDisconnected(AClientState* ClientState);
	virtual void OnClientDisconnected_Implementation(AClientState* ClientState);


	// GETTERS

	/** Returns the maximum number of clients that can connect to this server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual int64 GetMaxClients();

	/** Returns the total number of clients that are connected to this server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual int64 GetTotalClients();

	/** Returns the name of this server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual FName GetServerName();
};
