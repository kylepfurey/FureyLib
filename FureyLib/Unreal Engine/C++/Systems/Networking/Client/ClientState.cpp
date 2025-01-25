// .cpp
// Client Player State Script
// by Kyle Furey

// REQUIREMENT: ClientState.h

// Include this heading to use the class
#include "Networking/Client/ClientState.h"


// CONSTRUCTORS

// Default constructor.
AClientState::AClientState()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ClientName = TEXT("None");
}

// Object initializer constructor.
AClientState::AClientState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ClientName = TEXT("None");
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AClientState::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	AClient* Client = GetClient();

	if (IsValid(Client) && Client->IsMyClient())
	{
		if (Instance == nullptr)
		{
			Instance = this;
		}

		UNetwork* Network = UNetwork::GetNetwork();

		if (IsValid(Network))
		{
			FName Name = Network->GetClientName();

			if (Name != TEXT("None") && Name != FName())
			{
				SetClientName(GetClient(), Name);
			}
		}
	}
}

// Determines what variables can be replicated across the network.
void AClientState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Calls the base class's function.
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AClientState, ClientName);
}

// Called when this actor is destroyed.
void AClientState::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	if (Instance == this)
	{
		Instance = nullptr;
	}
}


// SINGLETON

// Returns a reference reference to the client player state.
AClientState* AClientState::GetInstance()
{
	return Instance;
}


// CLIENT

// Returns this client state's client if this game instance owns the client or is the server.
AClient* AClientState::GetClient()
{
	return Cast<AClient>(GetPlayerController());
}

// Returns whether the given client owns this client state.
bool AClientState::IsMyClient(AClient* _Owner)
{
	return _Owner == GetClient();
}


// EVENTS

// Automatically called when this client's names changes.
void AClientState::OnClientNameChanged_Implementation(FName OldName, FName NewName) {}


// GETTERS

// Returns the name of this client.
FName AClientState::GetClientName()
{
	return ClientName;
}


// SETTERS

// Sets the name of this client across the network.
void AClientState::SetClientName_Implementation(AClient* _Owner, FName _ClientName)
{
	if (IsMyClient(_Owner))
	{
		AServer* Server = UNetwork::GetServer();

		AClient* Client = GetClient();

		if (IsValid(Server) && IsValid(Client))
		{
			Server->ChangeName(Client, _ClientName.ToString(), ClientName == TEXT("None") || ClientName == FName());

			ClientName = _ClientName;
		}
	}
}

// Automatically called when this client's name is replicated.
void AClientState::OnRep_ClientName_Implementation()
{
	FName Name = ClientName;

	Rename(*(ClientName.ToString() + TEXT("'s State")));

	SetActorLabel(ClientName.ToString() + TEXT("'s State"));

	UNetwork* Network = UNetwork::GetNetwork();

	if (IsValid(Network))
	{
		Name = Network->GetClientName();

		AClient* Client = GetClient();

		if (IsValid(Client))
		{
			Client->Rename(*ClientName.ToString());

			Client->SetActorLabel(ClientName.ToString());

			if (Client->IsMyClient())
			{
				Network->SetClientName(ClientName);
			}
		}
	}

	OnClientNameChanged(Name, ClientName);
}


// NETWORK

// Returns the replicated state of this game instance's client.
AClientState* UNetwork::GetClientState()
{
	AClient* Client = UNetwork::MyClient();

	return IsValid(Client) ? Client->GetState() : nullptr;
}


// SERVER

// Safely handles when player controllers are swapped on a seamless level travel.
// NOTE: This should be called when OnSwapPlayerControllers() is called in blueprints.
void AServer::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	AClient* OldClient = Cast<AClient>(OldPC);

	AClient* NewClient = Cast<AClient>(NewPC);

	if (IsValid(OldClient) && IsValid(NewClient))
	{
		NewClient->SetClientID(OldClient->GetClientID());

		AClientState* OldClientState = OldClient->GetState();

		AClientState* NewClientState = NewClient->GetState();

		if (IsValid(OldClientState) && IsValid(NewClientState))
		{
			NewClientState->SetClientName(NewClient, OldClientState->GetClientName());
		}

		AllClients.Add(OldClient->GetClientID(), NewClient);
	}

	OnSwapPlayerControllers(OldClient, NewClient);
}


// CLIENT

// Returns the replicated state of this client.
AClientState* AClient::GetState()
{
	return GetPlayerState<AClientState>();
}


// STATIC VARIABLE INITIALIZATION

// A singleton reference to the client player state.
AClientState* AClientState::Instance = nullptr;
