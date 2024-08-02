// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinWidget.h"
#include "../LoginPlayerController.h"

void UJoinWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mIDInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IDInput")));
	mPassInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PassInput")));

	mJoinButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinButton")));
	mCancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	mJoinButton->OnClicked.AddDynamic(this, &UJoinWidget::JoinClick);
	mCancelButton->OnClicked.AddDynamic(this, &UJoinWidget::CancelClick);
}

void UJoinWidget::JoinClick()
{
	if (!IsEmptyInput())
	{
		ALoginPlayerController* Controller = Cast<ALoginPlayerController>(GetOwningPlayer());

		if (IsValid(Controller))
		{
			Controller->SendJoinInfo(mIDInput->GetText(), mPassInput->GetText());
		}
	}
}

void UJoinWidget::CancelClick()
{
	ClearInput();
	SetVisibility(ESlateVisibility::Collapsed);
}

void UJoinWidget::JoinComplete(bool Join)
{
	if (Join)
	{
		ClearInput();
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UJoinWidget::ClearInput()
{
	mIDInput->SetText(FText::FromString(TEXT("")));
	mPassInput->SetText(FText::FromString(TEXT("")));
}

bool UJoinWidget::IsEmptyInput()
{
	return mIDInput->GetText().IsEmpty() ||
		mPassInput->GetText().IsEmpty();
}

