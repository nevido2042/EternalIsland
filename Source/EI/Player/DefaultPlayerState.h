// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ADefaultPlayerState();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	mName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mExp;

public:
	int32 GetAttackDamage() const
	{
		return mAttackDamage;
	}


	int32 GetHP() const
	{
		return mHP;
	}

	int32 GetHPMax() const
	{
		return mMaxHP;
	}


	int32 GetLevel() const
	{
		return mLevel;
	}

	int32 GetExp() const
	{
		return mExp;
	}

	void InflictDamage(int Amount, FVector ImpactNormal = FVector(0.f));


public:
	void AddHP(int32 Amount)
	{


		int HP = mHP + Amount;

		if (HP >= mMaxHP)
			mHP = mMaxHP;
		else
			mHP = HP;

	}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
