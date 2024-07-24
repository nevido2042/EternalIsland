// Fill out your copyright notice in the Description page of Project Settings.


#include "EIGameModeBase.h"

AEIGameModeBase::AEIGameModeBase()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Player/Blueprint/BP_MainPlayer.BP_MainPlayer_C'"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Script/Engine.Blueprint'/Game/Player/Blueprint/BP_MainController.BP_MainController_C'"));
	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

}
