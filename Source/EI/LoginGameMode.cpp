// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "Player/LoginPlayerController.h"

ALoginGameMode::ALoginGameMode()
{
	PlayerControllerClass = ALoginPlayerController::StaticClass();
	
}

void ALoginGameMode::BeginPlay()
{
}
