// Fill out your copyright notice in the Description page of Project Settings.


#include "EIGameInstance.h"
#include "Network/NetworkManager.h"

UEIGameInstance::UEIGameInstance()
{
	mSelectJob = EPlayerJob::Swordsman;
}

UEIGameInstance::~UEIGameInstance()
{
}

// ÃÊ±âÈ­
void UEIGameInstance::Init()
{
	Super::Init();

	CNetworkManager::GetInst()->Init();
}


void UEIGameInstance::FinishDestroy()
{
	Super::FinishDestroy();

	LOG(TEXT("GameInstance FinishDestroy"));

	CNetworkManager::DestroyInst();
}