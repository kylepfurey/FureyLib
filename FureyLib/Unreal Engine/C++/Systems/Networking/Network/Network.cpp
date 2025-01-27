// .cpp
// Networking Game Instance Script
// by Kyle Furey

// REQUIREMENT: Network.h

// Include this heading to use the class
#include "Networking/Network/Network.h"


// CONSTRUCTORS

// Default constructor.
UNetwork::UNetwork()
{
	MainMenuLevelName = TEXT("None");

	NetStatus = ENetworkStatus::OFFLINE;

	Subsystem = nullptr;

	Session = nullptr;

	SessionSearch = nullptr;

	bSearching = false;

	SearchResults = {};

	MaxConnections = 0;

	ServerName = TEXT("None");

	ClientName = TEXT("None");

	OnCreateSessionCompleteCaptures =
	{
		FName(),
		0,
		FName(),
		FDelegateHandle()
	};

	OnFindSessionsCompleteHandle = FDelegateHandle();

	OnJoinSessionCompleteCaptures =
	{
		FString(),
		0,
		FDelegateHandle()
	};

	OnDestroySessionCompleteCaptures =
	{
		FName(),
		FDelegateHandle()
	};

	HandleNetworkErrorHandle = FDelegateHandle();

	HandleTravelErrorHandle = FDelegateHandle();
}

// Object initializer constructor.
UNetwork::UNetwork(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MainMenuLevelName = TEXT("None");

	NetStatus = ENetworkStatus::OFFLINE;

	Subsystem = nullptr;

	Session = nullptr;

	SessionSearch = nullptr;

	bSearching = false;

	SearchResults = {};

	MaxConnections = 0;

	ServerName = TEXT("None");

	ClientName = TEXT("None");

	OnCreateSessionCompleteCaptures =
	{
		FName(),
		0,
		FName(),
		FDelegateHandle()
	};

	OnFindSessionsCompleteHandle = FDelegateHandle();

	OnJoinSessionCompleteCaptures =
	{
		FString(),
		0,
		FDelegateHandle()
	};

	OnDestroySessionCompleteCaptures =
	{
		FName(),
		FDelegateHandle()
	};

	HandleNetworkErrorHandle = FDelegateHandle();

	HandleTravelErrorHandle = FDelegateHandle();
}


// HELPERS

// Returns the given level name, the current level name if LevelName == "Current", or the main menu level name if LevelName == "Menu".
FName UNetwork::GetLevelName(FName LevelName)
{
	FString Lowercase = LevelName.ToString().ToLower();

	if (Lowercase == TEXT("current"))
	{
		return FName(GetWorld()->GetName());
	}

	if (Lowercase == TEXT("menu"))
	{
		return MainMenuLevelName;
	}

	return LevelName;
}

// Sets the network status and invokes the OnNetStatusChanged() event.
void UNetwork::SetNetStatus(ENetworkStatus _NetStatus)
{
	ENetworkStatus OldStatus = NetStatus;

	NetStatus = _NetStatus;

	OnNetStatusChanged(OldStatus, NetStatus);
}

// The function bound and called when a new session is created.
void UNetwork::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		ServerName = OnCreateSessionCompleteCaptures.ServerName;

		MaxConnections = OnCreateSessionCompleteCaptures.MaxConnections;

		UGameplayStatics::OpenLevel(this, GetLevelName(OnCreateSessionCompleteCaptures.LevelToLoad), true, !IsDedicatedServerInstance() ? "listen" : "");

		Session->StartSession(ServerName);

		DELAY_FOR_TICK(
			{
				SetNetStatus(ENetworkStatus::HOSTING);

				OnHost();

				if (!IsDedicatedServerInstance())
				{
					OnConnect();
				}
			});
	}
	else
	{
		SetNetStatus(ENetworkStatus::OFFLINE);
	}

	if (Session.IsValid() && OnCreateSessionCompleteCaptures.Handle.IsValid())
	{
		Session->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteCaptures.Handle);
	}
}

// The function bound and called when sessions were found.
void UNetwork::OnFindSessionsComplete(bool bWasSuccessful)
{
	bSearching = false;

	SearchResults.Empty();

	if (bWasSuccessful && SessionSearch.IsValid())
	{
		TArray<FNetworkSession> Sessions;

		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			if (Result.IsValid())
			{
				Sessions.Add(FNetworkSession(Result));
			}
		}

		SearchResults = Sessions;

		OnSearchComplete(SearchResults);
	}

	if (Session.IsValid() && OnFindSessionsCompleteHandle.IsValid())
	{
		Session->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteHandle);
	}
}

// The function bound and called when a session is joined.
void UNetwork::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success && Session.IsValid())
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (IsValid(PlayerController))
		{
			FString ConnectString;

			if (Session->GetResolvedConnectString(SessionName, ConnectString))
			{
				ServerName = FName(OnJoinSessionCompleteCaptures.ServerName);

				MaxConnections = OnJoinSessionCompleteCaptures.MaxConnections;

				PlayerController->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);

				DELAY_FOR_TICK(
					{
						SetNetStatus(ENetworkStatus::CONNECTED);

						OnConnect();
					});

				return;
			}
		}
	}

	SetNetStatus(ENetworkStatus::OFFLINE);

	if (Session.IsValid() && OnJoinSessionCompleteCaptures.Handle.IsValid())
	{
		Session->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteCaptures.Handle);
	}
}

// The function bound and called when a hosted session is destroyed.
void UNetwork::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	SetNetStatus(ENetworkStatus::OFFLINE);

	MaxConnections = 0;

	ServerName = TEXT("None");

	UGameplayStatics::OpenLevel(this, GetLevelName(OnDestroySessionCompleteCaptures.LevelToLoad));

	if (Session.IsValid() && OnDestroySessionCompleteCaptures.Handle.IsValid())
	{
		Session->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteCaptures.Handle);
	}
}

// The function bound and called to handle network errors and disconnect.
void UNetwork::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	OnNetworkError(FailureType, ErrorString);

	Disconnect(TEXT("Main"), false);
}

// The function bound and called to handle travel errors and disconnect.
void UNetwork::OnTravelFailure(UWorld* InWorld, ETravelFailure::Type FailureType, const FString& ErrorString)
{
	OnTravelError(FailureType, ErrorString);

	Disconnect(TEXT("Main"), false);
}


// UNREAL FUNCTIONS

// Called when the game is first initialized.
void UNetwork::Init()
{
	// Calls the base class's function.
	Super::Init();

	if (Instance == nullptr)
	{
		Instance = this;
	}

	MainMenuLevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));

	Subsystem = IOnlineSubsystem::Get();

	if (Subsystem)
	{
		Session = Subsystem->GetSessionInterface();
	}

	if (IsValid(GEngine))
	{
		HandleNetworkErrorHandle = GEngine->OnNetworkFailure().AddUObject(this, &UNetwork::OnNetworkFailure);

		HandleTravelErrorHandle = GEngine->OnTravelFailure().AddUObject(this, &UNetwork::OnTravelFailure);
	}
}

// Called when the game's current world changes.
void UNetwork::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	// Calls the base class's function.
	Super::OnWorldChanged(OldWorld, NewWorld);

	// Call OnCurrentWorldChanged().
	OnCurrentWorldChanged(OldWorld, NewWorld);
}

// Called when the game is closed.
void UNetwork::Shutdown()
{
	// Calls the base class's function.
	Super::Shutdown();

	if (Instance == this)
	{
		Instance = nullptr;
	}

	if (IsValid(GEngine))
	{
		if (HandleNetworkErrorHandle.IsValid())
		{
			GEngine->OnNetworkFailure().Remove(HandleNetworkErrorHandle);
		}

		if (HandleTravelErrorHandle.IsValid())
		{
			GEngine->OnTravelFailure().Remove(HandleTravelErrorHandle);
		}
	}
}


// SINGLETON

// Returns a reference to the network game instance.
UNetwork* UNetwork::GetInstance()
{
	return Instance;
}


// NETWORK

// Hosts a new server and connects this game instance as a client.
// LevelToLoad can be passed as "Current" to reload the current level or "Menu" to load the main menu level.
bool UNetwork::Host(FName _ServerName, FName LevelToLoad, bool bPublic, int32 _MaxConnections, bool bUseLAN)
{
	if (NetStatus != ENetworkStatus::OFFLINE || _ServerName == TEXT("None") || _ServerName == FName() || !Session.IsValid())
	{
		return false;
	}

	ULocalPlayer* Player = GetFirstGamePlayer();

	if (!IsValid(Player))
	{
		return false;
	}

	FUniqueNetIdRepl ID = Player->GetPreferredUniqueNetId();

	if (!ID.IsValid())
	{
		return false;
	}

	FOnlineSessionSettings SessionSettings;
	SessionSettings.NumPublicConnections = bPublic ? _MaxConnections : 0;
	SessionSettings.NumPrivateConnections = bPublic ? 0 : _MaxConnections;
	SessionSettings.bShouldAdvertise = bPublic;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsLANMatch = bUseLAN;
	SessionSettings.bIsDedicated = IsDedicatedServerInstance();
	SessionSettings.bUsesStats = true;
	SessionSettings.bAllowInvites = true;
	SessionSettings.bUsesPresence = !IsDedicatedServerInstance();
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bAllowJoinViaPresenceFriendsOnly = !bPublic;
	SessionSettings.bAntiCheatProtected = bPublic;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bUseLobbiesVoiceChatIfAvailable = true;
	SessionSettings.Set(TEXT("LevelName"), LevelToLoad.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	if (OnCreateSessionCompleteCaptures.Handle.IsValid())
	{
		Session->OnCreateSessionCompleteDelegates.Remove(OnCreateSessionCompleteCaptures.Handle);
	}

	OnCreateSessionCompleteCaptures.ServerName = _ServerName;
	OnCreateSessionCompleteCaptures.MaxConnections = _MaxConnections;
	OnCreateSessionCompleteCaptures.LevelToLoad = LevelToLoad;
	OnCreateSessionCompleteCaptures.Handle = Session->OnCreateSessionCompleteDelegates.AddUObject(this, &UNetwork::OnCreateSessionComplete);

	if (Session->CreateSession(*ID, ServerName, SessionSettings))
	{
		SetNetStatus(ENetworkStatus::CONNECTING);

		return true;
	}

	return false;
}

// Searches asynchronously for other servers' online sessions to display and possibly connect to.
// When the search completes, OnSearchComplete() is called and the result is stored in SearchResults.
bool UNetwork::Search(int32 MaxResults, bool bUseLAN)
{
	if (bSearching || !Session.IsValid())
	{
		return false;
	}

	ULocalPlayer* Player = GetFirstGamePlayer();

	if (!IsValid(Player))
	{
		return false;
	}

	FUniqueNetIdRepl ID = Player->GetPreferredUniqueNetId();

	if (!ID.IsValid())
	{
		return false;
	}

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = MaxResults;
	SessionSearch->bIsLanQuery = bUseLAN;
	SessionSearch->PingBucketSize = 50;

	if (OnFindSessionsCompleteHandle.IsValid())
	{
		Session->OnFindSessionsCompleteDelegates.Remove(OnFindSessionsCompleteHandle);
	}

	OnFindSessionsCompleteHandle = Session->OnFindSessionsCompleteDelegates.AddUObject(this, &UNetwork::OnFindSessionsComplete);

	if (Session->FindSessions(*ID, SessionSearch.ToSharedRef()))
	{
		bSearching = true;

		OnSearch();

		return true;
	}

	return false;
}

// Attempts to connect to the given session asynchronously.
bool UNetwork::Connect(const FNetworkSession& JoinedSession)
{
	if (NetStatus != ENetworkStatus::OFFLINE || !Session.IsValid() || !JoinedSession.Session.IsValid())
	{
		return false;
	}

	ULocalPlayer* Player = GetFirstGamePlayer();

	if (!IsValid(Player))
	{
		return false;
	}

	FUniqueNetIdRepl ID = Player->GetPreferredUniqueNetId();

	if (!ID.IsValid())
	{
		return false;
	}

	if (OnJoinSessionCompleteCaptures.Handle.IsValid())
	{
		Session->OnJoinSessionCompleteDelegates.Remove(OnJoinSessionCompleteCaptures.Handle);
	}

	OnJoinSessionCompleteCaptures.ServerName = JoinedSession.Session.Session.OwningUserName;
	OnJoinSessionCompleteCaptures.MaxConnections = JoinedSession.Session.Session.SessionSettings.NumPublicConnections + JoinedSession.Session.Session.SessionSettings.NumPrivateConnections;
	OnJoinSessionCompleteCaptures.Handle = Session->OnJoinSessionCompleteDelegates.AddUObject(this, &UNetwork::OnJoinSessionComplete);

	if (Session->JoinSession(*ID, NAME_GameSession, JoinedSession.Session))
	{
		SetNetStatus(ENetworkStatus::CONNECTING);

		return true;
	}

	return false;
}

// Disconnects from the current session and either returns to the given level or quits the game if offline.
// LevelToLoad can be passed as "Current" to reload the current level or "Menu" to load the main menu level.
bool UNetwork::Disconnect(FName LevelToLoad, bool bQuitIfOffline)
{
	if (NetStatus == ENetworkStatus::OFFLINE && bQuitIfOffline)
	{
		UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);

		return true;
	}

	if (NetStatus == ENetworkStatus::DISCONNECTING || !Session.IsValid())
	{
		return false;
	}

	bool bIsHost = NetStatus == ENetworkStatus::HOSTING;

	SetNetStatus(ENetworkStatus::DISCONNECTING);

	if (bIsHost)
	{
		if (OnDestroySessionCompleteCaptures.Handle.IsValid())
		{
			Session->OnDestroySessionCompleteDelegates.Remove(OnDestroySessionCompleteCaptures.Handle);
		}

		OnDestroySessionCompleteCaptures.LevelToLoad = LevelToLoad;
		OnDestroySessionCompleteCaptures.Handle = Session->OnDestroySessionCompleteDelegates.AddUObject(this, &UNetwork::OnDestroySessionComplete);

		if (Session->DestroySession(NAME_GameSession))
		{
			OnDisconnect();

			return true;
		}

		return false;
	}
	else
	{
		OnDisconnect();

		bool bResult = Session->EndSession(NAME_GameSession);

		MaxConnections = 0;

		ServerName = TEXT("None");

		SetNetStatus(ENetworkStatus::OFFLINE);

		UGameplayStatics::OpenLevel(this, GetLevelName(LevelToLoad));

		return bResult;
	}
}


// EVENTS

// Automatically called when this game instance's current world changes.
void UNetwork::OnCurrentWorldChanged_Implementation(UWorld* OldWorld, UWorld* NewWorld) {}

// Automatically called when this game instance's network status changes.
void UNetwork::OnNetStatusChanged_Implementation(ENetworkStatus OldStatus, ENetworkStatus NewStatus) {}

// Automatically called when the main menu level name changes.
void UNetwork::OnMainMenuLevelNameChanged_Implementation(FName OldName, FName NewName) {}

// Automatically called when this game instance begins to host a server.
void UNetwork::OnHost_Implementation() {}

// Automatically called when this game instance begins searching for sessions.
void UNetwork::OnSearch_Implementation() {}

// Automatically called when this game instance completes its search for sessions.
void UNetwork::OnSearchComplete_Implementation(const TArray<FNetworkSession>& _SearchResults) {}

// Automatically called when this game instance successfully connects to a server.
void UNetwork::OnConnect_Implementation() {}

// Automatically called when this game instance disconnects from a server.
void UNetwork::OnDisconnect_Implementation() {}

// Automatically called when this game instance is forcefully kicked from a server.
void UNetwork::OnKick_Implementation(const FString& Reason) {}

// Automatically called when this game instance's client changes names.
void UNetwork::OnClientNameChanged_Implementation(FName OldName, FName NewName) {}

// Automatically called when a network error occurs.
void UNetwork::OnNetworkError_Implementation(ENetworkFailure::Type FailureType, const FString& ErrorString) {}

// Automatically called when a travel error occurs.
void UNetwork::OnTravelError_Implementation(ETravelFailure::Type FailureType, const FString& ErrorString) {}


// GETTERS

// Returns the global instance of the network.
UNetwork* UNetwork::GetNetwork()
{
	if (IsValid(GWorld))
	{
		return Cast<UNetwork>(UGameplayStatics::GetGameInstance(GWorld));
	}

	return nullptr;
}

// Returns the current world.
UWorld* UNetwork::GetCurrentWorld()
{
	return GWorld;
}

// Returns the time in seconds since the last game tick.
float UNetwork::GetDeltaTime()
{
	return UGameplayStatics::GetWorldDeltaSeconds(GWorld);
}

// Returns the time in seconds since the game started.
float UNetwork::GetElapsedTime()
{
	if (IsValid(GWorld))
	{
		return GWorld->GetTimeSeconds();
	}

	return 0;
}

// Returns the number of seconds since epoch (January 1, 1970, 00:00:00 UTC).
int64 UNetwork::GetEpochTime()
{
	return (FDateTime::UtcNow() - FDateTime(1970, 1, 1, 0, 0, 0)).GetTotalSeconds();
}

// Returns the name of the main menu level.
FName UNetwork::GetMainMenuLevelName()
{
	return MainMenuLevelName;
}

// Returns whether this game instance is connected to a server or is hosting one.
bool UNetwork::IsConnected()
{
	return NetStatus == ENetworkStatus::HOSTING || NetStatus == ENetworkStatus::CONNECTED || NetStatus == ENetworkStatus::DISCONNECTING;
}

// Returns whether this game instance is currently a client connected to a server.
bool UNetwork::IsRunningClient()
{
	return NetStatus == ENetworkStatus::CONNECTED;
}

// Returns whether this game instance is currently a hosting client and not a dedicated server.
bool UNetwork::IsRunningHost()
{
	return NetStatus == ENetworkStatus::HOSTING && !IsDedicatedServerInstance();
}

// Returns whether this game instance is currently a dedicated server and is not a client.
bool UNetwork::IsRunningDedicatedServer()
{
	return NetStatus == ENetworkStatus::HOSTING && IsDedicatedServerInstance();
}

// Returns the connection status of this game instance's client.
ENetworkStatus UNetwork::GetNetStatus()
{
	return NetStatus;
}

// Returns a pointer to the subsystem used to handle networking.
IOnlineSubsystem* UNetwork::GetSubsystem()
{
	return Subsystem;
}

// Returns a pointer to the current session of the network.
IOnlineSessionPtr UNetwork::GetSession()
{
	return Session;
}

// Returns a pointer to the search results of the network's current session.
FOnlineSessionSearchPtr UNetwork::GetSessionSearch()
{
	return SessionSearch;
}

// Returns whether this game instance is currently searching for sessions.
bool UNetwork::IsSearching()
{
	return bSearching;
}

// Returns the most recent search results of this game instance.
TArray<FNetworkSession>& UNetwork::GetSearchResults()
{
	return SearchResults;
}

// Returns the maximum number of connections allowed on the server if this game instance is the server.
int32 UNetwork::GetMaxConnections()
{
	return MaxConnections;
}

// Returns the name of the server that is being hosted or connected to.
FName UNetwork::GetServerName()
{
	return ServerName;
}

// Returns the last known name of this game instance's client.
FName UNetwork::GetClientName()
{
	return ClientName;
}


// SETTERS

// Sets the name of the main menu level.
void UNetwork::SetMainMenuLevelName(FName _MainMenuLevelName)
{
	FName OldName = MainMenuLevelName;

	MainMenuLevelName = _MainMenuLevelName;

	OnMainMenuLevelNameChanged(OldName, MainMenuLevelName);
}

// Sets the last known name of this game instance's client.
void UNetwork::SetClientName(FName _ClientName)
{
	FName OldName = ClientName;

	ClientName = _ClientName;

	OnClientNameChanged(OldName, ClientName);
}


// NETWORK SESSION

// Breaks the given FNetworkSession structure.
void UNetwork::BreakNetworkSession(const FNetworkSession& NetworkSession, FName& _ServerName, FString& ServerID, int32& PingInMs, int32& CurrentPlayers, int32& MaxPlayers)
{
	if (NetworkSession.Session.IsValid())
	{
		_ServerName = FName(NetworkSession.Session.Session.OwningUserName);

		ServerID = NetworkSession.Session.Session.GetSessionIdStr();

		PingInMs = NetworkSession.Session.PingInMs;

		MaxPlayers = NetworkSession.Session.Session.SessionSettings.NumPublicConnections + NetworkSession.Session.Session.SessionSettings.NumPrivateConnections;

		CurrentPlayers = MaxPlayers - NetworkSession.Session.Session.NumOpenPublicConnections;
	}
	else
	{
		_ServerName = TEXT("None");

		ServerID = "";

		PingInMs = 0;

		CurrentPlayers = 0;

		MaxPlayers = 0;
	}
}


// STATIC VARIABLE INITIALIZATION

// A singleton reference to the network game instance.
UNetwork* UNetwork::Instance = nullptr;
