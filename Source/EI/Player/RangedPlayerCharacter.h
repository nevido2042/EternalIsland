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

	ARangedPlayerCharacter();

	//virtual void BeginPlay() override;

	virtual void NormalAttack(APawn* InTarget) override;

	virtual void QSkill();

	virtual void WSkill();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;


	/*UFUNCTION(Server, Reliable)
	void SpawnProjecttile();
	void SpawnProjecttile_Implementation();*/
};
