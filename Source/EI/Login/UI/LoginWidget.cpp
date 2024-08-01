// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "../LoginPlayerController.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mPassInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PassInput")));
	mLoginButton = Cast<UButton>(GetWidgetFromName(TEXT("LoginButton")));
	mJoinButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinButton")));
	mJoinWidget = Cast<UJoinWidget>(GetWidgetFromName(TEXT("UI_Join")));

	mLoginButton->OnClicked.AddDynamic(this, &ULoginWidget::LoginClick);
	mJoinButton->OnClicked.AddDynamic(this, &ULoginWidget::JoinClick);
}
void ULoginWidget::LoginClick()
{
	ALoginPlayerController* Controller = Cast<ALoginPlayerController>(GetOwningPlayer());

	if (IsValid(Controller))
	{
		Controller->SendLoginInfo(IDInput->GetText(), mPassInput->GetText());
	}
}

void ULoginWidget::JoinClick()
{
	mJoinWidget->SetVisibility(ESlateVisibility::Visible);
}
