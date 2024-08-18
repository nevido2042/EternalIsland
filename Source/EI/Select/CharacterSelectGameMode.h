// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ACharacterSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACharacterSelectGameMode();

private:
	class CPacketQueue* mQueue;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
