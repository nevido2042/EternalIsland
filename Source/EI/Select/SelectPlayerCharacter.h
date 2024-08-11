// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Character.h"
#include "SelectPlayerCharacter.generated.h"

UCLASS()
class EI_API ASelectPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASelectPlayerCharacter();

protected:
	UPROPERTY(EditAnyWhere)
	EPlayerJob mJob;

public:
	EPlayerJob GetPlayerJob()	const
	{
		return mJob;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
