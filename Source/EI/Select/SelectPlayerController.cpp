// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerController.h"
#include "UI/CharacterSelectWidget.h"
#include "SelectPlayerCharacter.h"

ASelectPlayerController::ASelectPlayerController()
{
	bReplicates = true;
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>	SelectUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Game/UI/UI_CharacterSelect.UI_CharacterSelect_C'"));

	if (SelectUIClass.Succeeded())
		mSelectUIClass = SelectUIClass.Class;
}

void ASelectPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);

	if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
	{
		if (IsValid(mSelectUIClass))
		{
			mSelectUIWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), mSelectUIClass);

			if (IsValid(mSelectUIWidget))
			{
				mSelectUIWidget->AddToViewport();
			}
		}
	}
}
void ASelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
	//{
	//	//InputComponent->BindAction(TEXT("MouseClick"), EInputEvent::IE_Pressed,
	//	//	this, &ASelectPlayerController::MousePick);
	//}
}

void ASelectPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectPlayerController::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ASelectPlayerController, mSelectJob);
}

//void ASelectPlayerController::MousePick()
//{
//	if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
//	{
//		PickCharacter();
//	}
//}
//
//void ASelectPlayerController::PickCharacter()
//{
//	FHitResult	result;
//
//	bool Collision = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3,
//		false, result);
//
//	if (Collision)
//	{
//		ASelectPlayerCharacter* PickActor = Cast<ASelectPlayerCharacter>(result.GetActor());
//
//		if (IsValid(PickActor))
//		{
//			mSelectJob = PickActor->GetPlayerJob();
//
//			//SendSelectJob(mSelectJob);
//
//			USAC1GameInstance* GameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();
//
//			if (IsValid(GameInst))
//			{
//				// 클라이언트가 가지고 있는 GameInst의 SelectJob을 변경한다.
//				GameInst->ChangeSelectJob(mSelectJob);
//			}
//
//			mSelectUIWidget->EnableStartButton(true);
//		}
//	}
//
//	else
//	{
//		mSelectJob = EPlayerJob::None;
//		mSelectUIWidget->EnableStartButton(false);
//	}
//}
//
//void ASelectPlayerController::SendSelectJob_Implementation(EPlayerJob Job)
//{
//	mSelectJob = Job;
//
//	USAC1GameInstance* GameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();
//
//	if (IsValid(GameInst))
//	{
//		GameInst->ChangeSelectJob(mSelectJob);
//		LOG(TEXT("Change Job"));
//	}
//}
