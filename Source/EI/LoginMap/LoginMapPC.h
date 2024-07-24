// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginMapPC.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ALoginMapPC : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void CreateServer();
	void JoinServer(FName IP = "127.0.0.1");
};
