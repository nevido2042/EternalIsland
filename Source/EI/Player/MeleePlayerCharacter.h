// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MainPlayerCharacter.h"
#include "MeleePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EI_API AMeleePlayerCharacter : public AMainPlayerCharacter
{
	GENERATED_BODY()
	
	virtual void NormalAttack() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* NormalAttackMontage;
};
