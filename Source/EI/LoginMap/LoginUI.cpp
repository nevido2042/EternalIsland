// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void ULoginUI::NativeConstruct()
{
	Super::NativeConstruct();

	CreateServerBtn->OnClicked.AddDynamic(this, &ULoginUI::CreateServer);
	JoinServerBtn->OnClicked.AddDynamic(this, &ULoginUI::JoinServerHandler);
	//InputIPTextBox->OnTextChanged.AddDynamic();
	//IPTextBox->OnTextCommitted.AddDynamic(this, &ULoginUI::OnChatBoxTextCommitted);
}

void ULoginUI::CreateServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("TestMap"), true, ((FString)(L"Listen")));
}

void ULoginUI::JoinServer(FName IP = "127.0.0.1")
{
	UGameplayStatics::OpenLevel(GetWorld(), IP);
}

void ULoginUI::JoinServerHandler()
{
	JoinServer();
}

//void ULoginUI::OnChatBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
//{
//	if (CommitMethod != ETextCommit::OnEnter) { return; }
//
//	/*FName IP = TEXT("%s", Text.ToString());
//	JoinServer(IP);*/
//	JoinServer();
//}


