// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectGameMode.h"
#include "SelectPlayerController.h"
#include "SelectPawn.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ASelectPawn::StaticClass();
	PlayerControllerClass = ASelectPlayerController::StaticClass();
}

void ACharacterSelectGameMode::BeginPlay()
{
	Super::BeginPlay();
}
