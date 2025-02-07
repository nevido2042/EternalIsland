// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "LoginPlayerController.h"
#include "Network/NetworkManager.h"
#include "Network/ReceiveThread.h"
#include "Network/NetworkSession.h"
#include "Network/PacketQueue.h"

ALoginGameMode::ALoginGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = ALoginPlayerController::StaticClass();
}

void ALoginGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	CNetworkManager::GetInst()->SetServerType(EServerType::Login);

	CNetworkManager::GetInst()->Connect(TEXT("DedicateServer"),
		TEXT("192.168.0.118"), 10020);

	FThreadInfo* Info = CNetworkManager::GetInst()->CreateThread<CReceiveThread>(TEXT("DedicateServerThread"));

	((CReceiveThread*)Info->Worker)->SetSession(CNetworkManager::GetInst()->FindSession(TEXT("DedicateServer")));

	mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("DedicateServerThread_Queue"));

	// 일시정지 되어 있는 스레드를 동작시킨다.
	CNetworkManager::GetInst()->SuspendThread(TEXT("DedicateServerThread"), false);

	CNetworkManager::GetInst()->SendServerType(TEXT("DedicateServer"));
}

void ALoginGameMode::BeginPlay()
{
	//Super::BeginPlay();
	//
	//// 경로를 만들어준다.
	//FString	FullPath = FString::Printf(TEXT("%s%s"),
	//	*FPaths::ProjectSavedDir(), TEXT("Membership.txt"));
	//
	//// 해당 파일이 없을 경우 파일을 만들어준다.
	//if (!IFileManager::Get().FileExists(*FullPath))
	//{
	//	// 파일이 없을 경우 회원목록 파일을 만들어준다.
	//	FArchive* FileWriter = IFileManager::Get().CreateFileWriter(*FullPath);
	//
	//	if (FileWriter)
	//	{
	//		int32	Member = 0;
	//
	//		*FileWriter << Member;
	//
	//		FileWriter->Close();
	//		delete FileWriter;
	//	}
	//}
	//
	//FArchive* FileReader = IFileManager::Get().CreateFileReader(*FullPath);
	//
	//if (!FileReader)
	//	return;
	//
	//int32	Count = 0;
	//
	//*FileReader << Count;
	//
	//for (int32 i = 0; i < Count; ++i)
	//{
	//	// 회원 정보를 만들어준다.
	//	FJoinInfo	Info;
	//	Info.Login = false;
	//
	//	*FileReader << Info.ID;
	//	*FileReader << Info.Password;
	//
	//
	//	mJoinInfoMap.Add(Info.ID, Info);
	//}
	//
	//
	//FileReader->Close();
	//delete FileReader;
	Super::BeginPlay();

	FString	FullPath = FString::Printf(TEXT("%s%s"), *FPaths::ProjectSavedDir(), TEXT("Membership.txt"));

	if (!IFileManager::Get().FileExists(*FullPath))
	{
		FArchive* FileWriter = IFileManager::Get().CreateFileWriter(*FullPath);
		if (FileWriter)
		{
			int32	Member = 0;
			*FileWriter << Member;
			FileWriter->Close();
			delete FileWriter;
			UE_LOG(LogTemp, Warning, TEXT("Membership file created at %s"), *FullPath);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create membership file at %s"), *FullPath);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Membership file already exists at %s"), *FullPath);
	}

	FArchive* FileReader = IFileManager::Get().CreateFileReader(*FullPath);
	if (!FileReader)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to open membership file at %s"), *FullPath);
		return;
	}

	int32	Count = 0;
	*FileReader << Count;
	for (int32 i = 0; i < Count; ++i)
	{
		FJoinInfo	Info;
		Info.Login = false;
		*FileReader << Info.ID;
		*FileReader << Info.Password;
		mJoinInfoMap.Add(Info.ID, Info);
	}

	FileReader->Close();
	delete FileReader;

	UE_LOG(LogTemp, Warning, TEXT("Membership file loaded with %d entries"), Count);
}
void ALoginGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ALoginGameMode::JoinMembership(const FText& ID, const FText& Password)
{
	const FJoinInfo* Info = FindMemberInfo(ID.ToString());

	if(Info)
		return false;

	FJoinInfo	NewInfo;
	NewInfo.Login = false;
	NewInfo.ID = ID.ToString();
	NewInfo.Password = Password.ToString();

	mJoinInfoMap.Add(NewInfo.ID, NewInfo);

	// 파일이 없을 경우 회원목록 파일을 만들어준다.
	FString	FullPath = FString::Printf(TEXT("%s%s"),
		*FPaths::ProjectSavedDir(), TEXT("Membership.txt"));
	FArchive* FileWriter = IFileManager::Get().CreateFileWriter(*FullPath);

	if (FileWriter)
	{
		int32	Member = mJoinInfoMap.Num();

		*FileWriter << Member;

		for (auto iter = mJoinInfoMap.CreateIterator(); iter; ++iter)
		{
			*FileWriter << iter->Value.ID;
			*FileWriter << iter->Value.Password;
		}

		FileWriter->Close();
		delete FileWriter;
	}

	return true;
}

bool ALoginGameMode::LoginMember(const FText& ID, const FText& Password)
{
	//FJoinInfo* Info = FindMemberInfo(ID.ToString());
	//
	//if (!Info)
	//	return false;
	//
	//else if (Info->Password != Password.ToString() || Info->Login)
	//	return false;
	//
	//Info->Login = true;
	//
	//return true;
	FJoinInfo* Info = FindMemberInfo(ID.ToString());

	if (!Info)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginMember: No member found with ID %s"), *ID.ToString());
		return false;
	}
	else if (Info->Password != Password.ToString())
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginMember: Password mismatch for ID %s"), *ID.ToString());
		return false;
	}
	else if (Info->Login)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginMember: User with ID %s is already logged in"), *ID.ToString());
		return false;
	}

	Info->Login = true;
	UE_LOG(LogTemp, Warning, TEXT("LoginMember: Login successful for ID %s"), *ID.ToString());
	return true;
}

FJoinInfo* ALoginGameMode::FindMemberInfo(const FString& ID)
{
	//return mJoinInfoMap.Find(ID);
	FJoinInfo* FoundInfo = mJoinInfoMap.Find(ID);
	if (!FoundInfo)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindMemberInfo: Could not find member with ID %s"), *ID);
	}
	return FoundInfo;
}