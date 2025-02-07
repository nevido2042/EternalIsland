// Fill out your copyright notice in the Description page of Project Settings.


#include "Creep/CreepBase.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "Player/DefaultPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Player/DefaultPlayerState.h"
#include "Player/MainPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACreepBase::ACreepBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	bReplicates = true;


}

void ACreepBase::ChangeState(EState InState)
{
	State = InState;
	
	GetWorldTimerManager().ClearAllTimersForObject(this);

	switch (InState)
	{
	case EState::Wander:
	{
		//FTimerHandle WanderTimer;
		//GetWorldTimerManager().SetTimer(WanderTimer, this, &ACreepBase::MovePawnToRandomLocation, 1.f, true);

		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			AIController->StopMovement();
			//LookAt(Target->GetActorLocation());
		}


		FTimerHandle CheckTimer;
		FTimerDelegate CheckDelegate;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
		CheckDelegate.BindUFunction(this, "CheckSurroundingWithSphere", GetWorld(), 500.f, /*OutOverlaps,*/ ObjectTypes);
		GetWorldTimerManager().SetTimer(CheckTimer, CheckDelegate, 1.f, true);

		break;
	}
	case EState::Trace:
	{
		FTimerHandle FollowTimer;
		GetWorldTimerManager().SetTimer(FollowTimer, this, &ACreepBase::FollowTarget, 0.1f, true);

		break;
	}
	case EState::Attack:
	{
		if (!IsValid(Target))
		{
			ChangeState(EState::Wander);
			break;
		}

		MulticastPlayAttackMontage(AttackMontage);
		ApplyDamage();

		FTimerHandle AttackTimer;
		FTimerDelegate AttackDelegate;
		AttackDelegate.BindUFunction(this, "ChangeState", EState::Trace);
		GetWorldTimerManager().SetTimer(AttackTimer, AttackDelegate, 1.f, false);
		break;
	}
	default:
		break;
	}
}

void ACreepBase::MovePawnToRandomLocation()
{
	if (!HasAuthority())  return;// 서버에서만 실행
    
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem) return;
    
    FNavLocation RandomLocation;
    if (NavSystem->GetRandomReachablePointInRadius(GetActorLocation(), 500.0f, RandomLocation))
    {
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToLocation(RandomLocation);

			LookAt(RandomLocation);
        }
    }
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

void ACreepBase::CheckSurroundingWithSphere(UWorld* World, float Radius/*, TArray<FOverlapResult>& InOutOverlaps*/, TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
	// 오버랩 쿼리 파라미터 설정
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = false;
	QueryParams.AddIgnoredActor(this);

	// 오버랩 결과를 저장할 배열
	TArray<FOverlapResult> OverlapResults;

	// 스피어 형태로 오버랩 테스트 수행
	World->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, FCollisionObjectQueryParams(ObjectTypes), FCollisionShape::MakeSphere(Radius), QueryParams);

	// 결과를 OutOverlaps에 복사
	/*InOutOverlaps = OverlapResults;*/

	// 디버그용으로 스피어를 그려서 결과를 시각적으로 확인
	DrawDebugSphere(World, GetActorLocation(), Radius, 12, FColor::Green, false, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("%d"), OverlapResults.Num());

	AActor* ClosestActor = CalculateClosestActor(OverlapResults);
	if (ClosestActor)
	{
		SetTarget(ClosestActor);
	}
}

AActor* ACreepBase::CalculateClosestActor(TArray<FOverlapResult>& InOverlapResults)
{
	for (const FOverlapResult& Result : InOverlapResults)
	{
		AActor* OverlappingActor = Result.GetActor();
		if (OverlappingActor)
		{
			return OverlappingActor;
		}
	}
	return nullptr;
}

void ACreepBase::SetTarget(AActor* InActor)
{
	Target = InActor;

	ChangeState(EState::Trace);
}

void ACreepBase::FollowTarget()
{
	if (MaxTraceDist < CheckTargetDist())
	{
		LostTarget();
		return;
	}
	else if (AttackRange > CheckTargetDist())
	{
		ChangeState(EState::Attack);
		return;
	}

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToActor(Target);

		LookAt(Target->GetActorLocation());
	}
}

void ACreepBase::LookAt(FVector InLocation)
{
	// Calculate the direction to the target
	FVector Direction = (InLocation - GetActorLocation()).GetSafeNormal();
	FRotator NewRotation = Direction.Rotation();
	NewRotation = FRotator(0.f, NewRotation.Yaw - 90.f, 0.f);

	// Set the new rotation
	SetActorRotation(NewRotation);
}

float ACreepBase::CheckTargetDist()
{
	return FVector::Dist(Target->GetActorLocation(), GetActorLocation());
}

void ACreepBase::LostTarget()
{
	ChangeState(EState::Wander);
}

void ACreepBase::MulticastPlayAttackMontage_Implementation(UAnimMontage* Montage)
{
	SkeletalMeshComponent->GetAnimInstance()->Montage_Play(AttackMontage);
}

void ACreepBase::ApplyDamage()
{
	if (!Target) return;

	AMainPlayerCharacter* TargetCharacter = Cast<AMainPlayerCharacter>(Target);
	if(!TargetCharacter) return;

	/*ADefaultPlayerState* TargetState = Cast<ADefaultPlayerState>(TargetCharacter->GetPlayerState());
	if (!TargetState) return;*/

	UGameplayStatics::ApplyDamage(TargetCharacter, AttackDamage, nullptr, nullptr, nullptr);
	//TargetState->InflictDamage(AttackDamage);
}

float ACreepBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Destroy();
	return 0.0f;
}
