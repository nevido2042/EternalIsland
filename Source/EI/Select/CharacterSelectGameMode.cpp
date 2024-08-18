// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectGameMode.h"
#include "SelectPlayerController.h"
#include "SelectPawn.h"
#include "Network/NetworkManager.h"
#include "Network/ReceiveThread.h"
#include "Network/NetworkSession.h"
#include "Network/PacketQueue.h"


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

void ACharacterSelectGameMode::InitGame(const FString& MapName,
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	CNetworkManager::GetInst()->SetServerType(EServerType::Select);

	CNetworkManager::GetInst()->Connect(TEXT("DedicateServer"),
		TEXT("14.37.126.86"), 10020);

	FThreadInfo* Info = CNetworkManager::GetInst()->CreateThread<CReceiveThread>(TEXT("DedicateServerThread"));

	((CReceiveThread*)Info->Worker)->SetSession(CNetworkManager::GetInst()->FindSession(TEXT("DedicateServer")));

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("DedicateServerThread_Queue"));

	// 일시정지 되어 있는 스레드를 동작시킨다.
	CNetworkManager::GetInst()->SuspendThread(TEXT("DedicateServerThread"), false);

	CNetworkManager::GetInst()->SendServerType(TEXT("DedicateServer"));
}

APlayerController* ACharacterSelectGameMode::Login(UPlayer* NewPlayer,
	ENetRole InRemoteRole, const FString& Portal, const FString& Options,
	const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal,
		Options, UniqueId, ErrorMessage);

	// 옵션정보 읽어오기
	FString	ID;

	if (FParse::Value(*Options, TEXT("ID="), ID))
	{
		Cast<ASelectPlayerController>(result)->SetID(ID);
	}

	return result;
}

void ACharacterSelectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
