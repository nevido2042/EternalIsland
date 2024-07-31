// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALoginGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
