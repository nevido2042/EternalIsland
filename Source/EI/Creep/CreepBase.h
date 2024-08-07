// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CreepBase.generated.h"

enum class EState :uint8
{
	Wander,
	Trace,
	Attack
};

UCLASS()
class EI_API ACreepBase : public APawn
{
	GENERATED_BODY()

public:
	ACreepBase();

	EState State;
	void ChangeState(EState InState);

protected:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage = nullptr;
protected:
	void MovePawnToRandomLocation();
	FVector GetRandomLocationInRadius(float Radius);

	AActor* Target = nullptr;
	//TArray<FOverlapResult> OutOverlaps;

	UFUNCTION()
	void CheckSurroundingWithSphere(UWorld* World, float Radius, /*TArray<FOverlapResult>& InOutOverlaps,*/ TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);

	AActor* CalculateClosestActor(TArray<FOverlapResult>& InOverlapResults);

	void SetTarget(AActor* InActor);

	void FollowTarget();

	float MaxTraceDist = 800.f;
	float CheckTargetDist();
	void LostTarget();

	float AttackRange = 100.f;
};
