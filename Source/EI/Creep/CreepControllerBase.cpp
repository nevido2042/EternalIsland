// Fill out your copyright notice in the Description page of Project Settings.


#include "Creep/CreepControllerBase.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


void ACreepControllerBase::BeginPlay()
{
	Super::BeginPlay();
	MoveToRandomLocation();
}

void ACreepControllerBase::MoveToRandomLocation()
{
	FVector RandomLocation = GetRandomLocationInRadius(1000.0f); // 1000 유닛 반경 내 랜덤 위치
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
}

//void ACreepControllerBase::MoveToRandomLocation_Implementation()
//{
//	FVector RandomLocation = GetRandomLocationInRadius(1000.0f); // 1000 유닛 반경 내 랜덤 위치
//	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
//}

FVector ACreepControllerBase::GetRandomLocationInRadius(float Radius)
{
	FVector Origin = GetPawn()->GetActorLocation();
	FNavLocation RandomPoint;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys && NavSys->GetRandomReachablePointInRadius(Origin, Radius, RandomPoint)) {
		return RandomPoint.Location;
	}

	return FVector::ZeroVector;
}
