// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"
#include "UI/LoginWidget.h"

ALoginPlayerController::ALoginPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> LoginUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Game/LoginMap/UI_Login.UI_Login_C'"));

	if (LoginUIClass.Succeeded())
		mLoginUIClass = LoginUIClass.Class;
}

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);

	//switch (GetWorld()->GetNetMode())
	//{
	//case NM_Standalone:
	//	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	//		TEXT("Standalone"));
	//	LOG(TEXT("Standalone"));
	//	break;
	//case NM_DedicatedServer:
	//	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	//		TEXT("DedicatedServer"));
	//	LOG(TEXT("DedicatedServer"));
	//	break;
	//case NM_ListenServer:
	//	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	//		TEXT("ListenServer"));
	//	LOG(TEXT("ListenServer"));
	//	break;
	//case NM_Client:
	//	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	//		TEXT("Client"));
	//	LOG(TEXT("Client"));
	//	break;
	//}
	//
	//if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
	//{
	//	if (IsValid(mLoginUIClass))
	//	{
	//		mLoginUIWidget = CreateWidget<ULoginWidget>(GetWorld(), mLoginUIClass);
	//
	//		if (IsValid(mLoginUIWidget))
	//		{
	//			mLoginUIWidget->AddToViewport();
	//			LOG(TEXT("UI Create"));
	//		}
	//	}
	//}
}

void ALoginPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALoginPlayerController::SendLoginInfo_Implementation(const FText& DI,
	const FText& Password)
{
}
