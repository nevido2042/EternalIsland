// Fill out your copyright notice in the Description page of Project Settings.


#include "EIGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/DefaultPlayerState.h"

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
