// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
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
	UPROPERTY()
	TMap<FString, FJoinInfo>	mJoinInfoMap;
	//class CPacketQueue* mQueue;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool JoinMembership(const FText& ID, const FText& Password);
	bool LoginMember(const FText& ID, const FText& Password);

public:
	FJoinInfo* FindMemberInfo(const FString& ID);
};
