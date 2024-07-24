// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestMapPC.generated.h"

/**
 * 
 */

class UInputAction;
class UInputMappingContext;

UCLASS()
class EI_API ATestMapPC : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void MoveToClickPoint();

	FVector GetClickLocation();
};
