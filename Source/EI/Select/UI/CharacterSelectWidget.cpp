// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "EIGameInstance.h"
#include "../SelectPlayerController.h"

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));

	mStartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::StartClick);
}

void UCharacterSelectWidget::StartClick()
{ 
	UEIGameInstance* GameInst = GetWorld()->GetGameInstance<UEIGameInstance>();

	ASelectPlayerController* Ctrl = GetOwningPlayer<ASelectPlayerController>();

	// GameInstance�� ������ �ִ� ���� ������ ���´�.
	EPlayerJob	SelectJob = GameInst->GetSelectJob();

	// ������ �̿��Ͽ� �ɼ��� ������ش�.
	FString	Option = FString::Printf(TEXT("Job=%d?ID=%s"), (int32)SelectJob,
		*Ctrl->GetID());

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("192.168.0.118:10002"));
}

void UCharacterSelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}
