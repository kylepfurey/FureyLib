// .h
// Client Player Controller Script
// by Kyle Furey

// REQUIREMENTS: OnlineSubsystem, Server.h, Client.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Networking/Server/Server.h"
#include "Client.generated.h"

// Include this heading to use the class
// #include "Networking/Client/Client.h"

/** Represents an individual client player controller that can remotely connect and replicate to an authoritative server. */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API AClient : public APlayerController
{
	GENERATED_BODY()

protected:

	// SINGLETON

	/** A singleton reference to the client player controller. */
	static AClient* Instance;


	// CLIENT

	/**
	 * The unique ID representing this client across the network.
	 * An ID of -1 means this client has not received its ID yet.
	 */
	UPROPERTY(ReplicatedUsing = OnRep_ClientID, BlueprintReadOnly, BlueprintGetter = "GetClientID", Category = "Client")
	int64 ClientID = -1;

	/** The name of this client. */
	UPROPERTY(ReplicatedUsing = OnRep_ClientName, BlueprintReadOnly, BlueprintGetter = "GetClientName", Category = "Client")
	FName ClientName = TEXT("None");


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Determines what variables can be replicated across the network. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	// CLIENT

	/** Plays the given sound in 2D on the owning client. */
	UFUNCTION(Client, Reliable)
	void OnRep_PlaySound2D(USoundBase* Sound, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);
	virtual void OnRep_PlaySound2D_Implementation(USoundBase* Sound, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);

	/** Plays the given sound in 3D on the owning client. */
	UFUNCTION(Client, Reliable)
	void OnRep_PlaySoundAtLocation(USoundBase* Sound, FVector Position, FRotator Rotation, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);
	virtual void OnRep_PlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Position, FRotator Rotation, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);

public:

	// CONSTRUCTORS

	/** Default constructor. */
	AClient();

	/** Object initializer constructor. */
	AClient(const FObjectInitializer& ObjectInitializer);


	// SINGLETON

	/** Returns a reference to the client player controller. */
	static AClient* GetInstance();


	// CLIENT

	/** Returns whether this client is the game instance's client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual bool IsMyClient();

	/** Kicks this client from the server. */
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Client")
	void Kick(const FString& Reason);
	virtual void Kick_Implementation(const FString& Reason);

	/** Plays the given sound in 2D on each client. */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Client")
	void PlaySound2D(USoundBase* Sound, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);
	virtual void PlaySound2D_Implementation(USoundBase* Sound, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);

	/** Plays the given sound in 3D on each client. */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Client")
	void PlaySoundAtLocation(USoundBase* Sound, FVector Position, FRotator Rotation, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);
	virtual void PlaySoundAtLocation_Implementation(USoundBase* Sound, FVector Position, FRotator Rotation, float VolumeMultiplier = 1, float PitchMultiplier = 1, float StartTime = 0);


	// EVENTS

	/** Automatically called when this client receives its client ID. */
	UFUNCTION(BlueprintNativeEvent, Category = "Client")
	void OnClientIDAssigned(int64 _ClientID);
	virtual void OnClientIDAssigned_Implementation(int64 _ClientID);

	/** Automatically called when this client's names changes. */
	UFUNCTION(BlueprintNativeEvent, Category = "Client")
	void OnClientNameChanged(FName OldName, FName NewName);
	virtual void OnClientNameChanged_Implementation(FName OldName, FName NewName);


	// GETTERS

	/**
	 * Returns the unique ID representing this client.
	 * An ID of -1 means this client has not received its ID yet.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual int64 GetClientID();

	/** Returns the name of this client. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Client")
	virtual FName GetClientName();


	// SETTERS

	/**
	 * Sets the unique ID representing this client across the network.
	 * NOTE: This should ONLY be called by the server.
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Client")
	void SetClientID(int64 _ClientID);
	virtual void SetClientID_Implementation(int64 _ClientID);

	/** Automatically called when this client's ID is replicated. */
	UFUNCTION(BlueprintNativeEvent, Category = "Client")
	void OnRep_ClientID();
	virtual void OnRep_ClientID_Implementation();

	/** Sets the name of this client across the network. */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Client")
	void SetClientName(FName _ClientName);
	virtual void SetClientName_Implementation(FName _ClientName);

	/** Automatically called when this client's name is replicated. */
	UFUNCTION(BlueprintNativeEvent, Category = "Client")
	void OnRep_ClientName();
	virtual void OnRep_ClientName_Implementation();
};
