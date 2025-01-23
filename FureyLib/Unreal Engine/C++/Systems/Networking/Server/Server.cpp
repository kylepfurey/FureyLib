// .cpp
// Server Game Mode Base Script
// by Kyle Furey

// REQUIREMENT: Server.h

// Include this heading to use the class
#include "Networking/Server/Server.h"


// CONSTRUCTORS

// Default constructor.
AServer::AServer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseSeamlessTravel = true;

	UNetwork* Network = UNetwork::GetNetwork();

	if (!IsValid(Network))
	{
		MaxClients = 0;

		ServerName = TEXT("None");

		NextClientID = 0;

		AllClients = TMap<int64, AClient*>();

		return;
	}

	MaxClients = Network->GetMaxConnections();

	ServerName = Network->GetServerName();

	NextClientID = 0;

	AllClients = TMap<int64, AClient*>();
}

// Object initializer constructor.
AServer::AServer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseSeamlessTravel = true;

	UNetwork* Network = UNetwork::GetNetwork();

	if (!IsValid(Network))
	{
		MaxClients = 0;

		ServerName = TEXT("None");

		NextClientID = 0;

		AllClients = TMap<int64, AClient*>();

		return;
	}

	MaxClients = Network->GetMaxConnections();

	ServerName = Network->GetServerName();

	NextClientID = 0;

	AllClients = TMap<int64, AClient*>();
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AServer::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	if (Instance == nullptr)
	{
		Instance = this;
	}

	Rename(*ServerName.ToString());

	SetActorLabel(ServerName.ToString());
}


// SINGLETON

// Returns a reference to the server game mode base.
AServer* AServer::GetInstance()
{
	return Instance;
}


// SERVER

// Seamlessly moves the server to a new level with its clients.
bool AServer::Travel(FName LevelToLoad)
{
	if (GetWorld()->ServerTravel(LevelToLoad.ToString() + (!UNetwork::GetNetwork()->IsDedicatedServerInstance() ? "?listen" : ""), true, true))
	{
		OnTravel(GetWorld(), FName(GetWorld()->GetMapName()), LevelToLoad);
	}

	return false;
}


// EVENTS

// Automatically called when a new client connects to the server.
void AServer::OnClientConnected_Implementation(AClient* Client) {}

// Automatically called when a client disconnects from the server.
void AServer::OnClientDisconnected_Implementation(AClient* Client) {}

// Automatically called before the server travels to a new level.
void AServer::OnTravel_Implementation(UWorld* CurrentWorld, FName OldLevelName, FName NewLevelName) {}

// Automatically called when player controllers are swapped during seamless travel.
void AServer::OnSwapPlayerControllers_Implementation(AClient* OldClient, AClient* NewClient) {}


// GETTERS

// Returns the maximum number of clients that can connect to this server.
int64 AServer::GetMaxClients()
{
	return MaxClients;
}

// Returns the name of this server.
FName AServer::GetServerName()
{
	return ServerName;
}

// Peeks and returns the client ID that will be assigned to the next connnected client.
int64 AServer::GetNextClientID()
{
	return NextClientID;
}

// Returns a map of each client ID to its corresponding client.
TMap<int64, AClient*> AServer::GetAllClients()
{
	return AllClients;
}

// Returns the client with the given client ID or NULL if no client matched.
AClient* AServer::GetClient(int64 ClientID)
{
	AClient** Client = AllClients.Find(ClientID);

	return Client ? *Client : nullptr;
}

// Returns the total number of currently connected clients.
int64 AServer::TotalClients()
{
	return AllClients.Num();
}


// STATIC VARIABLE INITIALIZATION

// A singleton reference to the server game mode base.
AServer* AServer::Instance = nullptr;

// The next ID to assign to a connected client.
// These are unique and never reused.
int64 AServer::NextClientID = 0;
