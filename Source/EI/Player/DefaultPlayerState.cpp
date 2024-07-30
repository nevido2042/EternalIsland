// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "DefaultPlayerController.h"
#include "MainPlayerCharacter.h"
#include "Net/UnrealNetwork.h"

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