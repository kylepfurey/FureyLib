// .h
// Server Game Mode Base Script
// by Kyle Furey

// REQUIREMENTS: OnlineSubsystem, Network.h, Server.cpp, Client.cpp, ServerState.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Networking/Network/Network.h"
#include "Server.generated.h"

// Include this heading to use the class
// #include "Networking/Server/Server.h"

/**
 * Represents a game mode base where client player controllers can remotely connect to an authoritative server.
 * This class is only accessible by the machine running the server but can interact with its replicated clients.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API AServer : public AGameModeBase
{
	GENERATED_BODY()

protected:

	// SINGLETON

	/** A singleton reference to the server game mode base. */
	static AServer* Instance;


	// SERVER

	/**
	 * The next ID to assign to a connected client.
	 * These are unique and never reused.
	 */
	static int64 NextClientID;

	/** A map of each client ID to its corresponding client. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetAllClients", Category = "Server")
	TMap<int64, AClient*> AllClients = TMap<int64, AClient*>();


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called when this actor is destroyed. */
	virtual void BeginDestroy() override;

	/** Called when a player controller connects to this game mode base. */
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Called when a player controller leaves the game. */
	virtual void Logout(AController* ExitingPlayer) override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	AServer();

	/** Object initializer constructor. */
	AServer(const FObjectInitializer& ObjectInitializer);


	// UNREAL FUNCTIONS

	/**
	 * Safely handles when player controllers are swapped on a seamless level travel.
	 * NOTE: This should be called when OnSwapPlayerControllers() is called in blueprints.
	 */
	UFUNCTION(BlueprintCallable, Category = "Server")
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC);


	// SINGLETON

	/** Returns a reference to the server game mode base. */
	static AServer* GetInstance();


	// SERVER

	/** Seamlessly moves the server to a new level with its clients. */
	UFUNCTION(BlueprintCallable, Category = "Server")
	virtual bool Travel(FName LevelToLoad);


	// EVENTS

	/** Automatically called when a new client connects to the server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Server")
	void OnClientConnected(AClient* Client);
	virtual void OnClientConnected_Implementation(AClient* Client);

	/** Automatically called when a client disconnects from the server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Server")
	void OnClientDisconnected(AClient* Client);
	virtual void OnClientDisconnected_Implementation(AClient* Client);

	/** Automatically called before the server travels to a new level. */
	UFUNCTION(BlueprintNativeEvent, Category = "Server")
	void OnTravel(UWorld* CurrentWorld, FName OldLevelName, FName NewLevelName);
	virtual void OnTravel_Implementation(UWorld* CurrentWorld, FName OldLevelName, FName NewLevelName);

	/** Automatically called when player controllers are swapped during seamless travel. */
	UFUNCTION(BlueprintNativeEvent, Category = "Server")
	void OnSwapPlayerControllers(AClient* OldClient, AClient* NewClient);
	virtual void OnSwapPlayerControllers_Implementation(AClient* OldClient, AClient* NewClient);


	// GETTERS

	/** Peeks and returns the client ID that will be assigned to the next connnected client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual int64 GetNextClientID();

	/** Returns a map of each client ID to its corresponding client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual TMap<int64, AClient*> GetAllClients();

	/** Returns the client with the given client ID or NULL if no client matched. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual AClient* GetClient(int64 ClientID);

	/** Returns the total number of currently connected clients. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual int64 TotalClients();

	/** Returns the replicated state of this server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual AServerState* GetState();
};
