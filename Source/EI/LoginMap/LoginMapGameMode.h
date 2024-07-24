// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginMapGameMode.generated.h"

/**
 * 
 */

class  UUserWidget;
UCLASS()
class EI_API ALoginMapGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoginUIAsset;
	UUserWidget* LoginUI = nullptr;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	void CreateLoginUI();
	
};
