// Fill out your copyright notice in the Description page of Project Settings.

#include "EIGameModeBase.h"
#include "Player/MeleePlayerCharacter.h"
#include "Player/RangedPlayerCharacter.h"
#include "EIGameInstance.h"
#include "Network/NetworkManager.h"
#include "Network/ReceiveThread.h"
#include "Network/NetworkSession.h"
#include "Network/PacketQueue.h"
#include "Player/DefaultPlayerController.h"
#include "Player/DefaultPlayerState.h"  // 스테이트 헤더 추가
#include "TimerManager.h"

AEIGameModeBase::AEIGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_MeleeCharacter_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> ControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_DefaultPlayerController.BP_DefaultPlayerController_C'"));
	if (IsValid(ControllerClass.Class))
	{
		UE_LOG(LogTemp, Warning, TEXT("AEIGameModeBase PlayerCharacter FClassFinder Success"));
		PlayerControllerClass = ControllerClass.Class;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AEIGameModeBase PlayerCharacter FClassFinder Fail"));
}

void AEIGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEIGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	CNetworkManager::GetInst()->SetServerType(EServerType::Main);

	CNetworkManager::GetInst()->Connect(TEXT("DedicateServer"),
		TEXT("192.168.0.118"), 10020);

	FThreadInfo* Info = CNetworkManager::GetInst()->CreateThread<CReceiveThread>(TEXT("DedicateServerThread"));

	((CReceiveThread*)Info->Worker)->SetSession(CNetworkManager::GetInst()->FindSession(TEXT("DedicateServer")));

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("DedicateServerThread_Queue"));

	// �Ͻ����� �Ǿ� �ִ� �����带 ���۽�Ų��.
	CNetworkManager::GetInst()->SuspendThread(TEXT("DedicateServerThread"), false);

	CNetworkManager::GetInst()->SendServerType(TEXT("DedicateServer"));

	mCount = 0;
}
APlayerController* AEIGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	ADefaultPlayerState* PlayerState = NewPlayerController->GetPlayerState<ADefaultPlayerState>();

	if (PlayerState)
	{
		PlayerState->SetImmortal(true);
		UE_LOG(LogTemp, Warning, TEXT("Player joined, checking player count..."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState is invalid!"));
	}
	// 플레이어 수 체크 후 카운트다운 시작 여부 결정
	CheckAndStartCountdown();

	return NewPlayerController;
}


//APlayerController* AEIGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
//{
//	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal,
//		Options, UniqueId, ErrorMessage);

	//LOGSTRING(Options);
	//UE_LOG(LogTemp, Warning, TEXT("Options string: %s"), *Options);
	//
	//// GameInstance에서 직업 정보를 가져옴
	//UEIGameInstance* GameInst = GetWorld()->GetGameInstance<UEIGameInstance>();
	//if (IsValid(GameInst))
	//{
	//	EPlayerJob Job = GameInst->GetSelectJob();  // 선택된 직업 가져오기
	//
	//	UClass* PlayerPawnClass = nullptr;
	//
	//	// 직업에 따라 적절한 캐릭터 클래스를 로드
	//	switch (Job)
	//	{
	//	case EPlayerJob::Swordsman:
	//		PlayerPawnClass = StaticLoadClass(APawn::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_MeleeCharacter_C'"));
	//		break;
	//	case EPlayerJob::Gunslinger:
	//		PlayerPawnClass = StaticLoadClass(APawn::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_RangedCharacter.BP_RangedCharacter_C'"));
	//		break;
	//	}
	//
	//	// 올바른 클래스가 로드되었을 경우 DefaultPawnClass로 설정
	//	if (PlayerPawnClass != nullptr)
	//	{
	//		DefaultPawnClass = PlayerPawnClass;
	//		UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass set to: %s"), *PlayerPawnClass->GetName());
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("Failed to load PlayerPawnClass for job: %d"), (int32)Job);
	//	}
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("GameInstance is not valid"));
	//}
	//return result;
	////FString	ID;
	////if (FParse::Value(*Options, TEXT("ID="), ID))
	////{
	////	ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(result);
	////
	////	Ctrl->SetID(ID);
	////
	////	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	////		FString::Printf(TEXT("ID : %s"), *ID));
	////
	////	uint8	Packet[1016] = {};
	////
	////	int32	Length = 0;
	////	int32	IDLength = ID.Len();
	////
	////	FMemory::Memcpy(Packet, &IDLength, sizeof(int32));
	////	Length += sizeof(int32);
	////
	////	FMemory::Memcpy(Packet + Length, *ID, sizeof(TCHAR) * IDLength);
	////	Length += (sizeof(TCHAR) * IDLength);
	////
	////	CNetworkManager::GetInst()->Send(TEXT("DedicateServer"),
	////		(int32)EPacketHeader::PlayerInfo_Receive,
	////		Length, Packet);
	////}
	////
	////else
	////{
	////	ID = FString::Printf(TEXT("sac%d"), mCount);
	////	++mCount;
	////
	////	ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(result);
	////
	////	Ctrl->SetID(ID);
	////	LOGSTRING(ID);
	////	LOG(TEXT("ID Failed"));
	////}
	////
	////return result;
//	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
//
//	UE_LOG(LogTemp, Warning, TEXT("Player joined, checking player count..."));
//
//	// 플레이어 수 체크 후 카운트다운 시작 여부 결정
//	CheckAndStartCountdown();
//
//	return NewPlayerController;
//}

//void AEIGameModeBase::PostLogin(APlayerController* NewPlayer)
//{
//	Super::PostLogin(NewPlayer);
//
//	UE_LOG(LogTemp, Warning, TEXT("Player joined, checking player count..."));
//
//	// 플레이어 수 체크 후 카운트다운 시작 여부 결정
//	CheckAndStartCountdown();
//}

void AEIGameModeBase::CheckAndStartCountdown()
{
	// 현재 플레이어 수가 필요한 인원만큼 채워졌는지 확인
	if (GetNumPlayers() >= RequiredMinPlayers)
	{

		// 카운트다운 시작
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &AEIGameModeBase::StartGame, StartCountDown, false);

		UE_LOG(LogTemp, Warning, TEXT("All players are here. Game will start in 10 seconds"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough players. Waiting for more players..."));
	}
}

void AEIGameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Start"));

	// 모든 플레이어의 무적 상태 해제
	SetPlayersImmortal(false);

	// 플레이어들을 각각의 시작 지점으로 배치
	PositionPlayers();
}

void AEIGameModeBase::SetPlayersImmortal(bool bImmortal)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
		if (IsValid(PlayerController))
		{
			ADefaultPlayerState* PlayerState = PlayerController->GetPlayerState<ADefaultPlayerState>();
			if (IsValid(PlayerState))
			{
				PlayerState->SetImmortal(bImmortal);
				UE_LOG(LogTemp, Warning, TEXT("Player %s Immortal: %s"), *PlayerState->GetPlayerName(), bImmortal ? TEXT("True") : TEXT("False"));
			}
		}
	}
}


void AEIGameModeBase::PositionPlayers()
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	int32 PlayerIndex = 0;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
		if (IsValid(PlayerController) && PlayerIndex < PlayerStarts.Num())
		{
			AActor* StartPoint = PlayerStarts[PlayerIndex++];
			APawn* PlayerPawn = PlayerController->GetPawn();
			if (IsValid(PlayerPawn))
			{
				PlayerPawn->SetActorTransform(StartPoint->GetTransform());
				UE_LOG(LogTemp, Warning, TEXT("Player %s moved to start point"), *PlayerPawn->GetName());
			}
		}
	}
}

void AEIGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
