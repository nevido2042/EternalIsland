// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "../SelectPlayerController.h"

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mBackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));

	mStartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::StartClick);
	mBackButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::BackClick);
}

void UCharacterSelectWidget::StartClick()
{ 
	//UEIGameInstance* GameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();

	ASelectPlayerController* Ctrl = GetOwningPlayer<ASelectPlayerController>();

	// GameInstance가 가지고 있는 선택 직업을 얻어온다.
	//EPlayerJob	SelectJob = GameInst->GetSelectJob();

	// 직업을 이용하여 옵션을 만들어준다.
	//FString	Option = FString::Printf(TEXT("Job=%d?ID=%s"), (int32)SelectJob,
	//	*Ctrl->GetID());

	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("127.0.0.1:10002"), true, Option);
}

void UCharacterSelectWidget::BackClick()
{
}

void UCharacterSelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}
