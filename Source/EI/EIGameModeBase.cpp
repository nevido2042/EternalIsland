// Fill out your copyright notice in the Description page of Project Settings.

#include "EIGameModeBase.h"
#include "Player/DefaultPlayerController.h"
#include "Player/MeleePlayerCharacter.h"
#include "Player/RangedPlayerCharacter.h"
#include "EIGameInstance.h"
#include "Network/NetworkManager.h"
#include "Network/ReceiveThread.h"
#include "Network/NetworkSession.h"
#include "Network/PacketQueue.h"

AEIGameModeBase::AEIGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_MeleeCharacter_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//PlayerControllerClass = ADefaultPlayerController::StaticClass();
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
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal,
		Options, UniqueId, ErrorMessage);

	LOGSTRING(Options);

	// �ɼ����� �о����
	int32	CommandJob;

	if (FParse::Value(*Options, TEXT("Job="), CommandJob))
	{
		EPlayerJob Job = (EPlayerJob)CommandJob;

		LOG(TEXT("Job : %d"), (int32)CommandJob);

		UClass* PlayerPawnClass = nullptr;

		switch (Job)
		{
		//case EPlayerJob::Swordsman:
		//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_MeleeCharacter_C'"));
		//	if (PlayerPawnBPClass.Class != nullptr)
		//	{
		//		DefaultPawnClass = PlayerPawnBPClass.Class;
		//	}
		//	break;
		//case EPlayerJob::Gunslinger:
		//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_RangedCharacter.BP_RangedCharacter_C'"));
		//	if (PlayerPawnBPClass.Class != nullptr)
		//	{
		//		DefaultPawnClass = PlayerPawnBPClass.Class;
		//	}
		//	break;
		case EPlayerJob::Swordsman:
			PlayerPawnClass = StaticLoadClass(APawn::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_MeleeCharacter_C'"));
			break;
		case EPlayerJob::Gunslinger:
			PlayerPawnClass = StaticLoadClass(APawn::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_RangedCharacter_C'"));
			break;
		}

		if (PlayerPawnClass != nullptr)
		{
			DefaultPawnClass = PlayerPawnClass;
		}

		ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(result);

		Ctrl->SetJob(Job);
	}

	else
	{
		ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(result);

		Ctrl->SetJob(EPlayerJob::Swordsman);

		//DefaultPawnClass = AMeleePlayerCharacter::StaticClass();
		UClass* PlayerPawnClass = StaticLoadClass(APawn::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Game/Player/BluePrint/BP_MeleeCharacter.BP_MeleeCharacter_C'"));
		if (PlayerPawnClass != nullptr)
		{
			DefaultPawnClass = PlayerPawnClass;
		}
	}

	FString	ID;
	if (FParse::Value(*Options, TEXT("ID="), ID))
	{
		ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(result);

		Ctrl->SetID(ID);

		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			FString::Printf(TEXT("ID : %s"), *ID));

		uint8	Packet[1016] = {};

		int32	Length = 0;
		int32	IDLength = ID.Len();

		FMemory::Memcpy(Packet, &IDLength, sizeof(int32));
		Length += sizeof(int32);

		FMemory::Memcpy(Packet + Length, *ID, sizeof(TCHAR) * IDLength);
		Length += (sizeof(TCHAR) * IDLength);

		CNetworkManager::GetInst()->Send(TEXT("DedicateServer"),
			(int32)EPacketHeader::PlayerInfo_Receive,
			Length, Packet);
	}

	else
	{
		ID = FString::Printf(TEXT("sac%d"), mCount);
		++mCount;

		ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(result);

		Ctrl->SetID(ID);
		LOGSTRING(ID);
		LOG(TEXT("ID Failed"));
	}

	return result;
}



void AEIGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ReceiveThread���� �޾ƿ� ��Ŷ�� �ִ��� �Ǵ��Ѵ�.
	if (!mQueue->Empty())
	{
		int32	Header = 0, Length = 0;
		uint8	Packet[1016];

		mQueue->Pop(Header, Length, Packet);


		switch ((EPacketHeader)Header)
		{
			// Unreal -> Relay
		case EPacketHeader::PlayerInfo_Send:
			break;
			// Relay -> Unreal
		case EPacketHeader::PlayerInfo_Receive:
		{
			FString	ID;
			Length = 0;

			int32	IDLength = 0;

			FMemory::Memcpy(&IDLength, Packet, sizeof(int32));
			Length += sizeof(int32);

			TCHAR	ReadID[256] = {};
			FMemory::Memcpy(ReadID, Packet + Length, sizeof(TCHAR) * IDLength);
			Length += (sizeof(TCHAR) * IDLength);

			ID = ReadID;

			EPlayerJob	Job;
			FMemory::Memcpy(&Job, Packet + Length, sizeof(EPlayerJob));
			Length += sizeof(EPlayerJob);

			ADefaultPlayerController* Ctrl = Cast<ADefaultPlayerController>(GetWorld()->GetFirstPlayerController());

			if (Ctrl)
			{
				AMainPlayerCharacter* PlayerPawn = Ctrl->GetPawn<AMainPlayerCharacter>();

				if (PlayerPawn)
				{
					PlayerPawn->SetPlayerInfo(Job);
				}
			}
		}
		break;
		case EPacketHeader::LevelTransition:
		{
			Length = 0;
			int32	IDLength = 0;
			FMemory::Memcpy(&IDLength, Packet, sizeof(int32));
			Length += sizeof(int32);

			TCHAR	ID[256] = {};
			FMemory::Memcpy(ID, Packet + Length, sizeof(TCHAR) * IDLength);
			Length += (sizeof(TCHAR) * IDLength);

			EServerType	Type;

			FMemory::Memcpy(&Type, Packet + Length, sizeof(EServerType));

			TArray<AActor*>	CtrlArray;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(),
				ADefaultPlayerController::StaticClass(), CtrlArray);

			ADefaultPlayerController* Ctrl = nullptr;

			for (int32 i = 0; i < CtrlArray.Num(); ++i)
			{
				ADefaultPlayerController* CastCtrl =
					Cast<ADefaultPlayerController>(CtrlArray[i]);

				if (CastCtrl)
				{
					if (CastCtrl->GetID() == ID)
					{
						Ctrl = CastCtrl;
						break;
					}
				}
			}

			if (!Ctrl)
				break;

			//Ctrl->ClientLevelTransition(Type);
		}
		break;
		}
	}
}
