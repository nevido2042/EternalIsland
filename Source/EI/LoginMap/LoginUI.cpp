// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "LoginMap/LoginMapPC.h"

void ULoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	CreateServerBtn->OnClicked.AddDynamic(this, &ULoginUI::CreateServerHandler);
	JoinServerBtn->OnClicked.AddDynamic(this, &ULoginUI::JoinServerHandler);
	IPTextBox->OnTextCommitted.AddDynamic(this, &ULoginUI::OnIPBoxTextCommitted);
}

void ULoginUI::CreateServerHandler()
{
	ALoginMapPC* PC = Cast<ALoginMapPC>(GetOwningPlayer());
	if (PC)
	{
		PC->CreateServer();
	}
}

void ULoginUI::JoinServerHandler()
{
	FString STR = IPTextBox->Text.ToString();
	FName IP = FName(*STR);

	ALoginMapPC* PC = Cast<ALoginMapPC>(GetOwningPlayer());
	if (PC)
	{
		PC->JoinServer(IP);
	}
}

void ULoginUI::OnIPBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::OnEnter) { return; }

	FString STR = Text.ToString();
	FName IP = FName(*STR);

	ALoginMapPC* PC = Cast<ALoginMapPC>(GetOwningPlayer());
	if (PC)
	{
		PC->JoinServer(IP);
	}
}


