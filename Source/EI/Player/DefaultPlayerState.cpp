// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "DefaultPlayerController.h"
#include "MainPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Player/DefaultPlayerController.h"
#include "UI/MainWidget.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	bReplicates = true;

	mHP = 100;
	mMaxHP = mHP;
	mAttackDamage = 10;
}
void ADefaultPlayerState::InflictDamage(int Amount)
{
	if (bImmortal)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is immortal. No damage taken."));
		return;
	}
	AddHP(-Amount);

	if (mHP <= 0)
	{
		Cast<ADefaultPlayerController>(GetPlayerController())->ClearTimer();

		AMainPlayerCharacter* Character = Cast<AMainPlayerCharacter>(GetPlayerController()->GetCharacter());
		Character->Destroy();
	}
}

void ADefaultPlayerState::OnRep_HP()
{
	ADefaultPlayerController* DefaultPlayerController = Cast<ADefaultPlayerController>(GetPlayerController());

	if (!DefaultPlayerController) return;

	UUserWidget* UserWidget = DefaultPlayerController->GetMainWidget();

	if (UserWidget)
	{
		UMainWidget* MainWidget = Cast<UMainWidget>(UserWidget);
		MainWidget->UpdateHPBar((float)GetHP() / (float)GetHPMax());
	}
}

void ADefaultPlayerState::OnRep_Level()
{
}

void ADefaultPlayerState::OnRep_Exp()
{
}


void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();

}


void ADefaultPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefaultPlayerState, mHP);
	DOREPLIFETIME(ADefaultPlayerState, mMaxHP);
	DOREPLIFETIME(ADefaultPlayerState, mAttackDamage);
	DOREPLIFETIME(ADefaultPlayerState, mLevel);
	DOREPLIFETIME(ADefaultPlayerState, mExp);
	DOREPLIFETIME(ADefaultPlayerState, bImmortal);
}