// Fill out your copyright notice in the Description page of Project Settings.


#include "EIGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/DefaultPlayerState.h"
#include "EIGameInstance.h"

AEIGameModeBase::AEIGameModeBase()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_RangedCharacter.BP_RangedCharacter_C'"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_DefaultPlayerController.BP_DefaultPlayerController_C'"));
	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_DefaultPlayerState.BP_DefaultPlayerState_C'"));
	if (PlayerStateBPClass.Succeeded())
	{
		PlayerStateClass = PlayerStateBPClass.Class;
	}

}

void AEIGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEIGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AEIGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId,
		ErrorMessage);
}

APlayerController* AEIGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return nullptr;
}

void AEIGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AEIGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AEIGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
