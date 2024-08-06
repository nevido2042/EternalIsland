// Fill out your copyright notice in the Description page of Project Settings.


#include "Creep/CreepBase.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
ACreepBase::ACreepBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ACreepBase::ChangeState(EState InState)
{
	State = InState;
	
	GetWorldTimerManager().ClearAllTimersForObject(this);

	switch (InState)
	{
	case EState::Wander:
	{
		FTimerHandle WanderTimer;
		GetWorldTimerManager().SetTimer(WanderTimer, this, &ACreepBase::MoveToRandomLocation, 1.f, true);

		FTimerHandle CheckTimer;
		FTimerDelegate CheckDelegate;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		CheckDelegate.BindUFunction(this, "CheckSurroundingWithSphere", GetWorld(), 1000.f, OutOverlaps, ObjectTypes);
		GetWorldTimerManager().SetTimer(CheckTimer, CheckDelegate, 1.f, true);

		break;
	}
		
	case EState::Trace:
	{

		break;
	}
	case EState::Attack:
		break;
	default:
		break;
	}
}

void ACreepBase::MoveToRandomLocation_Implementation()
{
	MultiMoveToRandomLocation();
}

void ACreepBase::MultiMoveToRandomLocation_Implementation()
{
	FVector RandomLocation = GetRandomLocationInRadius(1000.0f); // 1000 유닛 반경 내 랜덤 위치
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), RandomLocation);
}

FVector ACreepBase::GetRandomLocationInRadius(float Radius)
{
	FVector Origin = GetActorLocation();
	FNavLocation RandomPoint;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys && NavSys->GetRandomReachablePointInRadius(Origin, Radius, RandomPoint)) {
		return RandomPoint.Location;
	}

	return FVector::ZeroVector;
}

void ACreepBase::CheckSurroundingWithSphere(UWorld* World, float Radius, TArray<FOverlapResult>& InOutOverlaps, TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
	// 오버랩 쿼리 파라미터 설정
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = false;

	// 오버랩 결과를 저장할 배열
	TArray<FOverlapResult> OverlapResults;

	// 스피어 형태로 오버랩 테스트 수행
	World->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, FCollisionObjectQueryParams(ObjectTypes), FCollisionShape::MakeSphere(Radius), QueryParams);

	// 결과를 OutOverlaps에 복사
	InOutOverlaps = OverlapResults;

	// 디버그용으로 스피어를 그려서 결과를 시각적으로 확인
	DrawDebugSphere(World, GetActorLocation(), Radius, 12, FColor::Green, false, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("%d"), OverlapResults.Num());
}
