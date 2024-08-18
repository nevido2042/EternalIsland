// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

public:
	ARangedPlayerCharacter();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void NormalAttack(APawn* InTarget) override;

	virtual void QSkill();

	virtual void WSkill();

	virtual void ESkill(const FVector& ClickLocation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystemComponent;

	FString			mLoginID;
	EPlayerJob		mJob;

	//UPROPERTY(EditAnywhere)
	//class UNiagaraComponent* NiagaraComponent;


	UFUNCTION(NetMulticast, Reliable)
	void MulticastActiveSystem();
	void MulticastActiveSystem_Implementation();

	//UFUNCTION(Server, Reliable)
	//void SpawnProjecttile();
	//void SpawnProjecttile_Implementation();
};
