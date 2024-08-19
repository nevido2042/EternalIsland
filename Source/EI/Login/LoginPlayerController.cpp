// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"
#include "LoginGameMode.h"
#include "UI/LoginWidget.h"
#include "UI/JoinWidget.h"

ALoginPlayerController::ALoginPlayerController()
{
	bReplicates = true;
	bShowMouseCursor = true;
	
	static ConstructorHelpers::FClassFinder<UUserWidget>	LoginUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Game/UI/UI_Login.UI_Login_C'"));
	
	if (LoginUIClass.Succeeded())
		mLoginUIClass = LoginUIClass.Class;

	mLoginSuccess = false;
	mJoinSuccess = false;
}

void ALoginPlayerController::OnRep_LoginSuccess()
{
}

void ALoginPlayerController::OnRep_JoinSuccess()
{
}

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);

	switch (GetWorld()->GetNetMode())
	{
	case NM_Standalone:
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			TEXT("Standalone"));
		LOG(TEXT("Standalone"));
		break;
	case NM_DedicatedServer:
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			TEXT("DedicatedServer"));
		LOG(TEXT("DedicatedServer"));
		break;
	case NM_ListenServer:
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			TEXT("ListenServer"));
		LOG(TEXT("ListenServer"));
		break;
	case NM_Client:
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			TEXT("Client"));
		LOG(TEXT("Client"));
		break;
	}
	
	if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
	{
		if (IsValid(mLoginUIClass))
		{
			mLoginUIWidget = CreateWidget<ULoginWidget>(GetWorld(), mLoginUIClass);
	
			if (IsValid(mLoginUIWidget))
			{
				mLoginUIWidget->AddToViewport();
				GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
					TEXT("!UI Create"));
				LOG(TEXT("!UI Create"));
				LOG(TEXT("UI Create"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
				TEXT("!mLoginUIWidget"));
			LOG(TEXT("!mLoginUIWidget"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			TEXT("!NM_Client"));
		LOG(TEXT("!NM_Client"));
	}
}

void ALoginPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoginPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALoginPlayerController, mLoginSuccess);
}


void ALoginPlayerController::SendLoginInfo_Implementation(const FText& ID,
	const FText& Password)
{
	ALoginGameMode* GameMode = GetWorld()->GetAuthGameMode<ALoginGameMode>();

	if (GameMode)
		mLoginSuccess = GameMode->LoginMember(ID, Password);
	
	SendClient(mLoginSuccess, ID.ToString());
}

void ALoginPlayerController::SendClient_Implementation(bool LoginSuccess, const FString& ID)
{
	//if (LoginSuccess)
	//{
	//	FString	Option = FString::Printf(TEXT("ID=%s"), *ID);
	//
 	//
	//	UGameplayStatics::OpenLevel(GetWorld(), TEXT("192.168.0.118:10001"));
	//}
	//
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	//		TEXT("Login Failed"));
	//	LOG(TEXT("Login Failed"));
	//}
	if (LoginSuccess)
	{
		FString	Option = FString::Printf(TEXT("ID=%s"), *ID);

		// 로그 추가
		UE_LOG(LogTemp, Warning, TEXT("Sending client to main level with ID: %s"), *ID);

		UGameplayStatics::OpenLevel(GetWorld(), TEXT("192.168.0.118:10001"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("Login Failed"));
		UE_LOG(LogTemp, Warning, TEXT("Login Failed for ID: %s"), *ID);
	}
}

void ALoginPlayerController::SendJoinInfo_Implementation(const FText& ID,
	const FText& Password)
{
	// 같은 ID가 회원 목록에 있는지 판단.
	ALoginGameMode* GameMode = GetWorld()->GetAuthGameMode<ALoginGameMode>();

	if (GameMode)
	{
		mJoinSuccess = GameMode->JoinMembership(ID, Password);
	}

	SendJoinClient(mJoinSuccess);
}

void ALoginPlayerController::SendJoinClient_Implementation(bool JoinSuccess)
{
	if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
	{
		if (IsValid(mLoginUIWidget))
		{
			mLoginUIWidget->GetJoinWidget()->JoinComplete(JoinSuccess);
		}
	}
}
