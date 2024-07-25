// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "DefaultPlayerController.h"
#include "MainPlayerCharacter.h"

ADefaultPlayerState::ADefaultPlayerState()
{
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

// Called when the game starts
void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// ...

}
