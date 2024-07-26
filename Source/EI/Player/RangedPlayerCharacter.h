// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MainPlayerCharacter.h"
#include "RangedPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ARangedPlayerCharacter : public AMainPlayerCharacter
{
	GENERATED_BODY()

protected:
	virtual void NormalAttack() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* NormalAttackMontage;
};
