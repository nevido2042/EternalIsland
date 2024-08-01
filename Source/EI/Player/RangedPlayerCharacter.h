// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerCharacter.h"
#include "Projectile/Projectile.h"
#include "RangedPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ARangedPlayerCharacter : public AMainPlayerCharacter
{
	GENERATED_BODY()

protected:

	virtual void NormalAttack(const APawn* InTarget) override;

	virtual void QSkill();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;
};
