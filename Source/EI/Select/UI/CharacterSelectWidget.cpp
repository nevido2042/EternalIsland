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

	// GameInstance가 가지고 있는 선택 직업을 얻어온다.
	EPlayerJob	SelectJob = GameInst->GetSelectJob();

	// 직업을 이용하여 옵션을 만들어준다.
	FString	Option = FString::Printf(TEXT("Job=%d?ID=%s"), (int32)SelectJob,
		*Ctrl->GetID());

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("14.37.126.86:10002"));
}

void UCharacterSelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}
