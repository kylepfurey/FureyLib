// .h
// Networking Game Instance Script
// by Kyle Furey

// REQUIREMENTS: OnlineSubsystem, Network.cpp, Client.cpp, ServerState.cpp, ClientState.cpp

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Network.generated.h"

// Include this heading to use the class
// #include "Networking/Network/Network.h"

// Whether an owning client has authority over their spawned objects.
#define OWNING_CLIENT_HAS_AUTHORITY 1

// Delays the given expression for the given number of seconds.
#define DELAY_FOR_SECONDS(Seconds, Expression) FTimerHandle Handle; GetWorld()->GetTimerManager().SetTimer(Handle, [this]Expression, Seconds, false);

// Delays the given expression until the next game tick.
#define DELAY_FOR_TICK(Expression) DELAY_FOR_SECONDS(0.0, Expression)

// A TSharedPtr to an FOnlineSessionSearch.
typedef TSharedPtr<FOnlineSessionSearch> FOnlineSessionSearchPtr;

// Forward declaration of server.
class AServer;

// Forward declaration of client.
class AClient;

// Forward declaration of server state.
class AServerState;

// Forward declaration of client state.
class AClientState;

/** The status of a client on the network. */
UENUM(BlueprintType, Category = "Network")
enum class ENetworkStatus : uint8
{
	OFFLINE = 0			UMETA(DisplayName = "Offline"),
	HOSTING = 1			UMETA(DisplayName = "Hosting"),
	CONNECTING = 2		UMETA(DisplayName = "Connecting"),
	CONNECTED = 3		UMETA(DisplayName = "Connected"),
	DISCONNECTING = 4	UMETA(DisplayName = "Disconnecting"),
	MAX					UMETA(Hidden)
};

/** Represents a single FOnlineSessionSearchResult but is blueprintable. */
USTRUCT(BlueprintType)
struct FNetworkSession final
{
	GENERATED_BODY()

public:

	// SESSION

	/** The underlying FOnlineSessionSearchResult class. */
	FOnlineSessionSearchResult Session;


	// CONSTRUCTORS

	/** Constructs an empty FNetworkSession. */
	FNetworkSession() { Session = {}; }

	/** Constructs a new FNetworkSession from a FOnlineSessionSearchResult. */
	FNetworkSession(const FOnlineSessionSearchResult& Session) : Session(Session) {}
};

/**
 * Represents a static game instance with functions and data related to client-server networking.
 * This class is only accessible by the device running the game and is purely used for storing persistent data between connections.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API UNetwork : public UGameInstance
{
	GENERATED_BODY()

protected:

	// SINGLETON

	/** A singleton reference to the network game instance. */
	static UNetwork* Instance;


	// MAIN MENU

	/**
	 * The name of the main menu level.
	 * This is the name of the game instance's first loaded level by default.
	 */
	UPROPERTY(BlueprintReadWrite, BlueprintGetter = "GetMainMenuLevelName", BlueprintSetter = "SetMainMenuLevelName", Category = "Network")
	FName MainMenuLevelName = TEXT("None");


	// NETWORK

	/** The connection status of this game instance's client. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetNetStatus", Category = "Network")
	ENetworkStatus NetStatus = ENetworkStatus::OFFLINE;

	/** A pointer to the subsystem used to handle networking. */
	IOnlineSubsystem* Subsystem = nullptr;

	/** A pointer to the current session of the network. */
	IOnlineSessionPtr Session = nullptr;

	/** A pointer to the search results of the network's current session. */
	FOnlineSessionSearchPtr SessionSearch = nullptr;

	/** Whether this game instance is currently searching for sessions. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "IsSearching", Category = "Network")
	bool bSearching = false;

	/** An array used to store session search results. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetSearchResults", Category = "Network")
	TArray<FNetworkSession> SearchResults = {};

	/** The maximum number of connections allowed if this game instance is the server. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetMaxConnections", Category = "Server")
	int32 MaxConnections = 0;

	/** The name of the server that is being hosted or connected to. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetServerName", Category = "Server")
	FName ServerName = TEXT("None");

	/** The last known name of this game instance's client. */
	UPROPERTY(BlueprintReadWrite, BlueprintGetter = "GetClientName", BlueprintSetter = "SetClientName", Category = "Client")
	FName ClientName = TEXT("None");


	// DELEGATES

	/** Captured variables and a delegate handle for the OnCreateSessionComplete delegate. */
	struct
	{
		FName ServerName = FName();
		int32 MaxConnections = 0;
		FName LevelToLoad = FName();
		FDelegateHandle Handle = FDelegateHandle();
	}
	OnCreateSessionCompleteCaptures;

	/** A delegate handle for the OnFindSessionsComplete delegate. */
	FDelegateHandle OnFindSessionsCompleteHandle = FDelegateHandle();

	/** Captured variables and a delegate handle for the OnJoinSessionComplete delegate. */
	struct
	{
		FString ServerName = FString();
		int32 MaxConnections = 0;
		FDelegateHandle Handle = FDelegateHandle();
	}
	OnJoinSessionCompleteCaptures;

	/** Captured variables and a delegate handle for the OnDestroySessionComplete delegate. */
	struct
	{
		FName LevelToLoad = FName();
		FDelegateHandle Handle = FDelegateHandle();
	}
	OnDestroySessionCompleteCaptures;

	/** A delegate handle for the network error event. */
	FDelegateHandle HandleNetworkErrorHandle = FDelegateHandle();

	/** A delegate handle for the travel error event. */
	FDelegateHandle HandleTravelErrorHandle = FDelegateHandle();


	// HELPERS

	/** Returns the given level name, the current level name if LevelName == "Current", or the main menu level name if LevelName == "Menu". */
	virtual FName GetLevelName(FName LevelName);

	/** Sets the network status and invokes the OnNetStatusChanged() event. */
	virtual void SetNetStatus(ENetworkStatus NetStatus);

	/** The function bound and called when a new session is created. */
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/** The function bound and called when sessions were found. */
	virtual void OnFindSessionsComplete(bool bWasSuccessful);

	/** The function bound and called when a session is joined. */
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/** The function bound and called when a hosted session is destroyed. */
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	/** The function bound and called to handle network errors and disconnect. */
	virtual void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	/** The function bound and called to handle travel errors and disconnect. */
	virtual void OnTravelFailure(UWorld* InWorld, ETravelFailure::Type FailureType, const FString& ErrorString);

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UNetwork();

	/** Object initializer constructor. */
	UNetwork(const FObjectInitializer& ObjectInitializer);


	// UNREAL FUNCTIONS

	/** Called when the game is first initialized. */
	virtual void Init() override;

	/** Called when the game's current world changes. */
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

	/** Called when the game is closed. */
	virtual void Shutdown() override;


	// SINGLETON

	/** Returns a reference to the network game instance. */
	static UNetwork* GetInstance();


	// NETWORK

	/**
	 * Hosts a new server and connects this game instance as a client.
	 * LevelToLoad can be passed as "Current" to reload the current level or "Menu" to load the main menu level.
	 */
	UFUNCTION(BlueprintCallable, Category = "Network")
	virtual bool Host(FName _ServerName, FName LevelToLoad = TEXT("Current"), bool bPublic = true, int32 _MaxConnections = 16, bool bUseLAN = false);

	/**
	 * Searches asynchronously for other servers' online sessions to display and possibly connect to.
	 * When the search completes, OnSearchComplete() is called and the result is stored in SearchResults.
	 */
	UFUNCTION(BlueprintCallable, Category = "Network")
	virtual bool Search(int32 MaxResults = 10, bool bUseLAN = false);

	/** Attempts to connect to the given session asynchronously. */
	UFUNCTION(BlueprintCallable, Category = "Network")
	virtual bool Connect(const FNetworkSession& JoinedSession);

	/**
	 * Disconnects from the current session and either returns to the given level or quits the game if offline.
	 * LevelToLoad can be passed as "Current" to reload the current level or "Menu" to load the main menu level.
	 */
	UFUNCTION(BlueprintCallable, Category = "Network")
	virtual bool Disconnect(FName LevelToLoad = TEXT("Menu"), bool bQuitIfOffline = true);


	// EVENTS

	/** Automatically called when this game instance's current world changes. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnCurrentWorldChanged(UWorld* OldWorld, UWorld* NewWorld);
	virtual void OnCurrentWorldChanged_Implementation(UWorld* OldWorld, UWorld* NewWorld);

	/** Automatically called when the main menu level name changes. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnMainMenuLevelNameChanged(FName OldName, FName NewName);
	virtual void OnMainMenuLevelNameChanged_Implementation(FName OldName, FName NewName);

	/** Automatically called when this game instance's network status changes. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnNetStatusChanged(ENetworkStatus OldStatus, ENetworkStatus NewStatus);
	virtual void OnNetStatusChanged_Implementation(ENetworkStatus OldStatus, ENetworkStatus NewStatus);

	/** Automatically called when this game instance begins to host a server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnHost();
	virtual void OnHost_Implementation();

	/** Automatically called when this game instance begins searching for sessions. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnSearch();
	virtual void OnSearch_Implementation();

	/** Automatically called when this game instance completes its search for sessions. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnSearchComplete(const TArray<FNetworkSession>& _SearchResults);
	virtual void OnSearchComplete_Implementation(const TArray<FNetworkSession>& _SearchResults);

	/** Automatically called when this game instance successfully connects to a server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnConnect();
	virtual void OnConnect_Implementation();

	/** Automatically called when this game instance disconnects from a server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnDisconnect();
	virtual void OnDisconnect_Implementation();

	/** Automatically called when this game instance is forcefully kicked from a server. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnKick(const FString& Reason);
	virtual void OnKick_Implementation(const FString& Reason);

	/** Automatically called when this game instance's client changes names. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnClientNameChanged(FName OldName, FName NewName);
	virtual void OnClientNameChanged_Implementation(FName OldName, FName NewName);

	/** Automatically called when a network error occurs. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnNetworkError(ENetworkFailure::Type FailureType, const FString& ErrorString);
	virtual void OnNetworkError_Implementation(ENetworkFailure::Type FailureType, const FString& ErrorString);

	/** Automatically called when a travel error occurs. */
	UFUNCTION(BlueprintNativeEvent, Category = "Network")
	void OnTravelError(ETravelFailure::Type FailureType, const FString& ErrorString);
	virtual void OnTravelError_Implementation(ETravelFailure::Type FailureType, const FString& ErrorString);


	// GETTERS

	/** Returns the global instance of the network. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	static UNetwork* GetNetwork();

	/** Returns the current world. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	static UWorld* GetCurrentWorld();

	/** Returns the time in seconds since the last game tick. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	static float GetDeltaTime();

	/** Returns the time in seconds since the game started. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	static float GetElapsedTime();

	/** Returns the number of seconds since epoch (January 1, 1970, 00:00:00 UTC). */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	static int64 GetEpochTime();

	/** Returns the name of the main menu level. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual FName GetMainMenuLevelName();

	/** Returns whether this game instance is connected to a server or is hosting one. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual bool IsConnected();

	/** Returns whether this game instance is currently a client connected to a server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual bool IsRunningClient();

	/** Returns whether this game instance is currently a hosting client and not a dedicated server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual bool IsRunningHost();

	/** Returns whether this game instance is currently a dedicated server and is not a client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual bool IsRunningDedicatedServer();

	/** Returns the connection status of this game instance's client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual ENetworkStatus GetNetStatus();

	/** Returns a pointer to the subsystem used to handle networking. */
	virtual IOnlineSubsystem* GetSubsystem();

	/** Returns a pointer to the current session of the network. */
	virtual IOnlineSessionPtr GetSession();

	/** Returns a pointer to the search results of the network's current session. */
	virtual FOnlineSessionSearchPtr GetSessionSearch();

	/** Returns whether this game instance is currently searching for sessions. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual bool IsSearching();

	/** Returns the most recent search results of this game instance. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network")
	virtual TArray<FNetworkSession>& GetSearchResults();

	/** Returns the maximum number of connections allowed on the server if this game instance is the server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual int32 GetMaxConnections();

	/** Returns the name of the server that is being hosted or connected to. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	virtual FName GetServerName();

	/** Returns the last known name of this game instance's client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual FName GetClientName();

	/**
	 * Returns the server instance if this game instance has authority.
	 * NOTE: This will return NULL if the current game instance is not a server or host!
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	static AServer* GetServer();

	/** Returns whether this game instance's client has authority over the server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	static bool HasAuthority();

	/**
	 * Returns this game instance's client.
	 * NOTE: This will return NULL if the current game instance is a dedicated server!
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	static AClient* MyClient();

	/** Returns the replicated state of this game instance's server. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Server")
	static AServerState* GetServerState();

	/** Returns the replicated state of this game instance's client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	static AClientState* GetClientState();

	/** Returns whether this game instance's client is the owner of the given actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ownership")
	static bool IsOwnerOf(AActor* Actor);

	/** Returns whether the given client owns the given actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ownership")
	static bool IsOwnedBy(AActor* Actor, AClient* Client);


	// SETTERS

	/** Overwrites the name of the main menu level. */
	UFUNCTION(BlueprintCallable, Category = "Network")
	virtual void SetMainMenuLevelName(FName _MainMenuLevelName);

	/** Updates the last known name of this game instance's client. */
	UFUNCTION(BlueprintCallable, Category = "Client")
	virtual void SetClientName(FName _ClientName);


	// NETWORK SESSION

	/** Breaks the given FNetworkSession structure. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Network Session")
	static void BreakNetworkSession(const FNetworkSession& NetworkSession, FName& _ServerName, FString& ServerID, int32& PingInMs, int32& CurrentPlayers, int32& MaxPlayers);
};
