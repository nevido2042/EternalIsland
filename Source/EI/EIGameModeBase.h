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
	//virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

private:
	class CPacketQueue* mQueue;
	int32	mCount;
	FTimerHandle GameStartTimer;  // 게임 시작 타이머 핸들
	float StartCountDown = 10.0f; // 무적 상태 유지 시간 (10초)
	int32 RequiredMinPlayers = 2; // 최소 필요한 플레이어 수

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void Tick(float DeltaTime) override;

private:
	void StartGame();  // 게임 시작 함수
	void SetPlayersImmortal(bool bImmortal);  // 플레이어 무적 설정 함수
	void PositionPlayers();  // 플레이어 배치 함수
	void CheckAndStartCountdown(); // 플레이어 수를 체크하고 카운트다운 시작
};
