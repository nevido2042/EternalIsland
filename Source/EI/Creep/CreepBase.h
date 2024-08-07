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
	// Sets default values for this pawn's properties
	ACreepBase();

	EState State;
	void ChangeState(EState InState);

	//virtual void BeginPlay() override;

protected:
	void MovePawnToRandomLocation();
protected:
	//void MoveToRandomLocation();
	////void MoveToRandomLocation_Implementation();
	//UFUNCTION(Server, Reliable, WithValidation)
	//void ServerMoveToRandomLocation();
	//bool ServerMoveToRandomLocation_Validate();

	//UFUNCTION(NetMulticast, UnReliable)
	//void MultiMoveToRandomLocation();
	//void MultiMoveToRandomLocation_Implementation();

	FVector GetRandomLocationInRadius(float Radius);

	APawn* Target = nullptr;
	TArray<FOverlapResult> OutOverlaps;

	UFUNCTION()
	void CheckSurroundingWithSphere(UWorld* World, float Radius, TArray<FOverlapResult>& InOutOverlaps, TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);
};
