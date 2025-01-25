// .cpp
// Server Game State Base Script
// by Kyle Furey

// REQUIREMENT: ServerState.h

// Include this heading to use the class
#include "Networking/Server/ServerState.h"


// CONSTRUCTORS

// Default constructor.
AServerState::AServerState()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	MaxClients = 0;

	TotalClients = 0;

	ServerName = TEXT("None");
}

// Object initializer constructor.
AServerState::AServerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	MaxClients = 0;

	TotalClients = 0;

	ServerName = TEXT("None");
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AServerState::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	if (Instance == nullptr)
	{
		Instance = this;
	}

	UNetwork* Network = UNetwork::GetNetwork();

	if (IsValid(Network))
	{
		MaxClients = Network->GetMaxConnections();

		ServerName = Network->GetServerName();

		Rename(*(ServerName.ToString() + TEXT("'s State")));

		SetActorLabel(ServerName.ToString() + TEXT("'s State"));
	}
}

// Determines what variables can be replicated across the network.
void AServerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Calls the base class's function.
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AServerState, MaxClients);

	DOREPLIFETIME(AServerState, TotalClients);

	DOREPLIFETIME(AServerState, ServerName);
}

// Called when this actor is destroyed.
void AServerState::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	if (Instance == this)
	{
		Instance = nullptr;
	}
}


// SINGLETON

// Returns a reference to the server game state base.
AServerState* AServerState::GetInstance()
{
	return Instance;
}


// SERVER

// Returns the server if this game instance has authority. 
AServer* AServerState::GetServer()
{
	return UNetwork::GetServer();
}


// EVENTS

// Automatically called when a new client connects to the server.
void AServerState::OnClientConnected_Implementation(AClientState* ClientState) {}

// Automatically called when a client disconnects from the server.
void AServerState::OnClientDisconnected_Implementation(AClientState* ClientState) {}


// GETTERS

// Returns the maximum number of clients that can connect to this server.
int64 AServerState::GetMaxClients()
{
	return MaxClients;
}

// Returns the total number of clients that are connected to this server.
int64 AServerState::GetTotalClients()
{
	return TotalClients;
}

// Returns the name of this server.
FName AServerState::GetServerName()
{
	return ServerName;
}


// NETWORK

// Returns the replicated state of this game instance's server.
AServerState* UNetwork::GetServerState()
{
	AServer* Server = UNetwork::GetServer();

	return IsValid(Server) ? Server->GetState() : nullptr;
}


// SERVER

// Called when a player controller connects to this game mode base.
void AServer::PostLogin(APlayerController* NewPlayer)
{
	// Calls the base class's function.
	Super::PostLogin(NewPlayer);

	AClient* Client = Cast<AClient>(NewPlayer);

	if (IsValid(Client))
	{
		AllClients.Add(NextClientID, Client);

		Client->SetClientID(NextClientID);

		++NextClientID;

		OnClientConnected(Client);

		AServerState* State = GetState();

		if (IsValid(State))
		{
			++State->TotalClients;

			State->OnClientConnected(Client->GetState());
		}
	}
}

// Called when a player controller leaves the game.
void AServer::Logout(AController* ExitingPlayer)
{
	// Calls the base class's function.
	Super::Logout(ExitingPlayer);

	AClient* Client = Cast<AClient>(ExitingPlayer);

	if (IsValid(Client))
	{
		AServerState* State = GetState();

		if (IsValid(State))
		{
			--State->TotalClients;

			State->OnClientDisconnected(Client->GetState());
		}

		OnClientDisconnected(Client);

		AllClients.Remove(Client->GetClientID());
	}
}

// Returns the replicated state of this server.
AServerState* AServer::GetState()
{
	return GetGameState<AServerState>();
}


// STATIC VARIABLE INITIALIZATION

// A singleton reference to the server game state base.
AServerState* AServerState::Instance = nullptr;
