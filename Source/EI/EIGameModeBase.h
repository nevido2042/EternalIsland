// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "EIGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EI_API AEIGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEIGameModeBase();

	virtual void BeginPlay() override;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Logout(AController* Exiting);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
