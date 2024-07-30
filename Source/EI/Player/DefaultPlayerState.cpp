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
void ADefaultPlayerState::InflictDamage(int Amount, FVector ImpactNormal)
{
	AddHP(-Amount);

	//쓰레기값을 가져오는 에러
	UUserWidget* UserWidget = nullptr;// = Cast<ADefaultPlayerController>(GetPlayerController())->GetMainWidget();

	if (UserWidget)
	{
		//그런데 이 안으로 들어옴
		/*UMainWidget* MainWidget = Cast<UMainWidget>(UserWidget);
		MainWidget->UpdateHPBar((float)mHP / (float)mMaxHP);*/
	}
	if (mHP <= 0)
	{
		AMainPlayerCharacter* Character = Cast<AMainPlayerCharacter>(GetPlayerController()->GetCharacter());
		Character->Destroy();
	}
}

void ADefaultPlayerState::OnRep_HP()
{
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
}