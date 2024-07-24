// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EI_API UPlayerStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateComponent();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	mName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32	mHPMax;

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
		return mHPMax;
	}


	int32 GetLevel() const
	{
		return mLevel;
	}

	int32 GetExp() const
	{
		return mExp;
	}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
