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


private:
	class CPacketQueue* mQueue;
	int32	mCount;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
