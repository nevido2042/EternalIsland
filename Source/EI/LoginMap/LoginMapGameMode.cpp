// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginMapGameMode.h"
#include "Blueprint/UserWidget.h"

void ALoginMapGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	CreateLoginUI();
}

void ALoginMapGameMode::CreateLoginUI()
{
	LoginUI = CreateWidget(GetWorld(), LoginUIAsset);
	LoginUI->AddToViewport();
}
