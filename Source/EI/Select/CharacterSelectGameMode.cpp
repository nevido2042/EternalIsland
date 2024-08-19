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
		TEXT("192.168.0.118"), 10020);

	FThreadInfo* Info = CNetworkManager::GetInst()->CreateThread<CReceiveThread>(TEXT("DedicateServerThread"));

	((CReceiveThread*)Info->Worker)->SetSession(CNetworkManager::GetInst()->FindSession(TEXT("DedicateServer")));

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("DedicateServerThread_Queue"));

	// �Ͻ����� �Ǿ� �ִ� �����带 ���۽�Ų��.
	CNetworkManager::GetInst()->SuspendThread(TEXT("DedicateServerThread"), false);

	CNetworkManager::GetInst()->SendServerType(TEXT("DedicateServer"));
}

APlayerController* ACharacterSelectGameMode::Login(UPlayer* NewPlayer,
	ENetRole InRemoteRole, const FString& Portal, const FString& Options,
	const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal,
		Options, UniqueId, ErrorMessage);

	// �ɼ����� �о����
	FString	ID;

	//if (FParse::Value(*Options, TEXT("ID="), ID))
	//{
	//	Cast<ASelectPlayerController>(result)->SetID(ID);
	//}
	if (FParse::Value(*Options, TEXT("ID="), ID))
	{
		// ID 값이 제대로 파싱되었는지 확인하기 위해 로그를 찍습니다.
		UE_LOG(LogTemp, Warning, TEXT("CharacterSelectGameMode: ID found: %s"), *ID);
		Cast<ASelectPlayerController>(result)->SetID(ID);
	}
	else
	{
		// ID 값이 파싱되지 않은 경우 로그를 찍습니다.
		UE_LOG(LogTemp, Warning, TEXT("CharacterSelectGameMode: ID not found in Options"));
	}
	return result;
}

void ACharacterSelectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
