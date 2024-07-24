// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginMap/LoginMapPC.h"
#include "Kismet/GameplayStatics.h"

void ALoginMapPC::BeginPlay()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());
}

void ALoginMapPC::CreateServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("TestMap"), true, ((FString)(L"Listen")));
}

void ALoginMapPC::JoinServer(FName IP)
{
	UGameplayStatics::OpenLevel(GetWorld(), IP);
}
