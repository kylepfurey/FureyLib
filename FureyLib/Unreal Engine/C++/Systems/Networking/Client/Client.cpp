// .cpp
// Client Player Controller Script
// by Kyle Furey

// REQUIREMENT: Client.h

// Include this heading to use the class
#include "Networking/Client/Client.h"


// CONSTRUCTORS

// Default constructor.
AClient::AClient()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ClientID = -1;
}

// Object initializer constructor.
AClient::AClient(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ClientID = -1;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AClient::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	if (IsMyClient())
	{
		if (Instance == nullptr)
		{
			Instance = this;
		}
	}
}

// Determines what variables can be replicated across the network.
void AClient::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Calls the base class's function.
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AClient, ClientID);
}

// Called when this actor is destroyed.
void AClient::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	if (Instance == this)
	{
		Instance = nullptr;
	}
}


// SINGLETON

// Returns a reference to the client player controller.
AClient* AClient::GetInstance()
{
	return Instance;
}


// CLIENT

// Returns whether this client is the game instance's client.
bool AClient::IsMyClient()
{
	return IsLocalController();
}

// Kicks this client from the server.
void AClient::Kick_Implementation(const FString& Reason)
{
	UNetwork* Network = UNetwork::GetNetwork();

	if (IsValid(Network))
	{
		ENetworkStatus NetStatus = Network->GetNetStatus();

		if (NetStatus == ENetworkStatus::CONNECTING || NetStatus == ENetworkStatus::CONNECTED)
		{
			Network->OnKick(Reason);

			Network->Disconnect(TEXT("Menu"), false);
		}
	}
}

// Plays the given sound in 2D on each client.
void AClient::PlaySound2D_Implementation(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	AServer* Server = UNetwork::GetServer();

	if (IsValid(Server))
	{
		TArray<AClient*> AllClients;

		Server->GetAllClients().GenerateValueArray(AllClients);

		for (AClient* Client : AllClients)
		{
			if (IsValid(Client))
			{
				Client->OnRep_PlaySound2D(Sound, VolumeMultiplier, PitchMultiplier, StartTime);
			}
		}
	}
}

// Plays the given sound in 2D on the owning client.
void AClient::OnRep_PlaySound2D_Implementation(USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	UGameplayStatics::PlaySound2D(this, Sound, VolumeMultiplier, PitchMultiplier, StartTime);
}

// Plays the given sound in 3D on each client.
void AClient::PlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Position, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	AServer* Server = UNetwork::GetServer();

	if (IsValid(Server))
	{
		TArray<AClient*> AllClients;

		Server->GetAllClients().GenerateValueArray(AllClients);

		for (AClient* Client : AllClients)
		{
			if (IsValid(Client))
			{
				Client->OnRep_PlaySoundAtLocation(Sound, Position, Rotation, VolumeMultiplier, PitchMultiplier, StartTime);
			}
		}
	}
}

// Plays the given sound in 3D on the owning client.
void AClient::OnRep_PlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Position, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime)
{
	UGameplayStatics::PlaySoundAtLocation(this, Sound, Position, Rotation, VolumeMultiplier, PitchMultiplier, StartTime);
}


// EVENTS

// Automatically called when this client receives its client ID.
void AClient::OnClientIDAssigned_Implementation(int64 _ClientID) {}


// GETTERS

// Returns the unique ID representing this client.
// An ID of -1 means this client has not received its ID yet.
int64 AClient::GetClientID()
{
	return ClientID;
}


// SETTERS

// Sets the unique ID representing this client across the network.
// NOTE: This should ONLY be called by the server.
void AClient::SetClientID_Implementation(int64 _ClientID)
{
	if (ClientID == -1)
	{
		ClientID = _ClientID;
	}
}

// Automatically called when this client's ID is replicated.
void AClient::OnRep_ClientID_Implementation()
{
	OnClientIDAssigned(ClientID);
}


// NETWORK

// Returns the server instance if this game instance has authority.
// NOTE: This will return NULL if the current game instance is not a server or host!
AServer* UNetwork::GetServer()
{
	AClient* Client = MyClient();

	if (IsValid(Client) && !Client->HasAuthority())
	{
		return nullptr;
	}

	if (IsValid(GWorld))
	{
		return Cast<AServer>(UGameplayStatics::GetGameMode(GWorld));
	}

	return nullptr;
}

// Returns whether this game instance's client has authority over the server.
bool UNetwork::HasAuthority()
{
	UNetwork* Network = UNetwork::GetNetwork();

	if (IsValid(Network) && Network->IsDedicatedServerInstance())
	{
		return true;
	}

	AClient* Client = MyClient();

	if (IsValid(Client))
	{
		return Client->HasAuthority();
	}

	return false;
}

// Returns this game instance's client.
// NOTE: This will return NULL if the current game instance is a dedicated server!
AClient* UNetwork::MyClient()
{
	UNetwork* Network = UNetwork::GetNetwork();

	if (IsValid(Network) && Network->IsDedicatedServerInstance())
	{
		return nullptr;
	}

	if (IsValid(GWorld))
	{
		return Cast<AClient>(UGameplayStatics::GetPlayerController(GWorld, 0));
	}

	return nullptr;
}

// Returns whether this game instance's client is the owner of the given actor.
bool UNetwork::IsOwnerOf(AActor* Actor)
{
	if (IsValid(Actor))
	{
		return Actor->GetOwner() == MyClient();
	}

	return false;
}

// Returns whether the given client owns the given actor.
bool UNetwork::IsOwnedBy(AActor* Actor, AClient* Client)
{
	if (IsValid(Actor))
	{
		return Actor->GetOwner() == Client;
	}

	return false;
}


// STATIC VARIABLE INITIALIZATION

// A singleton reference to the client player controller.
AClient* AClient::Instance = nullptr;
