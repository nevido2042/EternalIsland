// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/MainPlayerCharacter.h"
#include "MeleePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EI_API AMeleePlayerCharacter : public AMainPlayerCharacter
{
	GENERATED_BODY()
	
public:
	AMeleePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void NormalAttack(APawn* InTarget) override;

	virtual void QSkill();

	virtual void WSkill();

	virtual void ESkill(const FVector& ClickLocation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystemComponent;

	//UPROPERTY(EditAnywhere)
	//class UNiagaraComponent* NiagaraComponent;


	UFUNCTION(NetMulticast, Reliable)
	void MulticastActiveSystem();
	void MulticastActiveSystem_Implementation();
};
