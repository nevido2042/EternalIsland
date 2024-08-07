// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "EI/Player/DefaultPlayerController.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create state
	//mState = CreateDefaultSubobject<ADefaultPlayerState>(TEXT("State"));

	// Set Collision.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetMesh()->SetCollisionProfileName(TEXT("Player"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = true; // Don't want to pull camera in when it collides with level

	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagMaxDistance = 800.f;
	CameraBoom->CameraLagSpeed = 4.f;

	GetMesh()->SetupAttachment(GetCapsuleComponent());
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight())); // Position the mesh
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	bReplicates = true;
}



// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	//APlayerController* PC = Cast<APlayerController>(GetController());
	//if (PC)
	//{
	//	mState = PC->GetPlayerState<ADefaultPlayerState>();
	//	if (!mState)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("PlayerState is not valid in BeginPlay"));
	//	}
	//}

	mState = GetPlayerState<ADefaultPlayerState>();
}
void AMainPlayerCharacter::NormalAttack(const APawn* InTarget)
{
	if (!InTarget)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("NormalAttack Called"));

	if (NormalAttackMontage)
	{
		MulticastPlayAttackMontage(NormalAttackMontage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NormalAttackMontage is not set"));
	}

	ADefaultPlayerState* targetState = Cast<ADefaultPlayerState>(InTarget->GetPlayerState());
	ADefaultPlayerState* MyState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (!targetState || !MyState)
	{
		return;
	}
	targetState->InflictDamage(MyState->GetAttackDamage(), InTarget->GetActorLocation());
}

void AMainPlayerCharacter::QSkill()
{
}

void AMainPlayerCharacter::NormalAttackHitCheck(float Radius , float Height)
{
	UE_LOG(LogTemp, Log, TEXT("NormalAttackHitCheck Called"));
	FHitResult result;
	FCollisionQueryParams param(NAME_None, false, this);

	FVector StartLoc = GetActorLocation();
	StartLoc.Z += 100.f;
	FVector EndLoc = StartLoc + GetActorForwardVector() * Height * 2.f;
	FQuat CapsuleRot = FQuat::MakeFromRotator(FRotator(90.f, GetActorRotation().Yaw, 0.0f));
	
	GetWorld()->SweepSingleByChannel(
		result,
		StartLoc, EndLoc,
		CapsuleRot,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeCapsule(Radius, Height), param);

	DrawDebugSphere(GetWorld(), StartLoc, 10.f, 32, FColor::Green, false, 1.f);
	DrawDebugSphere(GetWorld(), EndLoc, 10.f, 32, FColor::Red, false, 1.f);
	DrawDebugCapsule(
		GetWorld(),											// 월드 컨텍스트
		(StartLoc + EndLoc) / 2.f,								// 캡슐의 중심 위치
		Height,												// 캡슐의 반 높이 (전체 높이의 절반)
		Radius,												// 캡슐의 반지름
		CapsuleRot,									// 캡슐의 회전 (기본적으로 회전 없음)
		FColor::Red,										// 캡슐의 색상
		false,												// 지속적으로 드로우 (true면 지속적으로, false면 한 번만)
		0.5f
	);

	AActor* HitActor = result.GetActor();
	if (!IsValid(HitActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack - HitActor Is Not Valid"));
		return;
	}

	AMainPlayerCharacter* targetCharacter = Cast<AMainPlayerCharacter>(HitActor);
	if (!IsValid(targetCharacter))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack - targetCharacter Is Not Valid"));
		return;
	}

	//ADefaultPlayerState* targetState = targetCharacter->GetPlayerState<ADefaultPlayerState>();
	ADefaultPlayerState* targetState = Cast<ADefaultPlayerState>(targetCharacter->GetPlayerState());
	ADefaultPlayerState* MyState = Cast<ADefaultPlayerState>(GetPlayerState());

	if (!IsValid(targetState))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack - targetState Is Not Valid"));
		return;
	}

	if (!MyState)
	{
		return;
	}

	targetState->InflictDamage(MyState->GetAttackDamage(), result.ImpactNormal);
	UE_LOG(LogTemp, Warning, TEXT("Hit Successe"));
}

void AMainPlayerCharacter::LookAtMousePos(const FVector& TargetLocation)
{
	//ADefaultPlayerController* Cont = Cast<ADefaultPlayerController>(GetController());
	//FVector TargetLocation = Cont->GetClickLocation();
	//FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	//LookAtRotator = FRotator(0.f, LookAtRotator.Yaw, 0.f);
	//SetActorRotation(LookAtRotator);
	//
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	LookAtRotator = FRotator(0.f, LookAtRotator.Yaw, 0.f);
	SetActorRotation(LookAtRotator);
}

void AMainPlayerCharacter::MulticastPlayAttackMontage_Implementation(UAnimMontage* Montage)
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
}

float AMainPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMainPlayerCharacter::InflictDamageTo(FHitResult result, float Multiplier)
{
}

void AMainPlayerCharacter::DrawNomalAttackDebug(FVector CenterLocation, FQuat SocketRotation, AActor* HitActor)
{
}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainPlayerCharacter::MoveToLocation(const FVector& Location)
{
	//Destination = Location;
	//bMoveToDestination = true;
	
	
	//if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	//{
	//	NavPath = NavSystem->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), Location);
	//
	//	if (NavPath && NavPath->PathPoints.Num() > 0)
	//	{
	//		bMoveToDestination = true;
	//		Destination = Location;
	//	}
	//}

	if (HasAuthority()) // 서버에서만 경로를 계산
	{
		if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), Location);

			if (NavPath && NavPath->PathPoints.Num() > 0)
			{
				PathPoints = NavPath->PathPoints; // 경로 점들을 저장
				bMoveToDestination = true;
				Destination = Location;

				// 클라이언트에 경로 점들을 동기화
				OnRep_PathPoints();
			}
		}
	}
}

void AMainPlayerCharacter::OnRep_PathPoints()
{
	// 클라이언트에서 경로를 따라 이동 시작
	bMoveToDestination = true;
}

//ADefaultPlayerState* AMainPlayerCharacter::GetPlayerState() const
//{
//	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
//	{
//		return Cast<ADefaultPlayerState>(PC->PlayerState);
//	}
//	return nullptr;
//}


// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (bMoveToDestination)
	//{
	//	FVector CurrentLocation = GetActorLocation();
	//	float Distance = FVector::Dist(CurrentLocation, Destination);
	//
	//	if (Distance > 100.0f) // Close enough to stop
	//	{
	//		FVector Direction = (Destination - CurrentLocation).GetSafeNormal();
	//		AddMovementInput(Direction, 1.0f);
	//	}
	//	else
	//	{
	//		bMoveToDestination = false;
	//	}
	//}
	 
	 
	//if (bMoveToDestination && NavPath && NavPath->PathPoints.Num() > 0)
	//{
	//	FVector CurrentLocation = GetActorLocation();
	//	FVector DestinationPoint = NavPath->PathPoints[0]; // 변경된 부분
	//
	//	float Distance = FVector::Dist(CurrentLocation, DestinationPoint);
	//
	//	if (Distance < 100.0f) // 목표 지점에 도착했는지 확인
	//	{
	//		NavPath->PathPoints.RemoveAt(0); // 다음 지점으로 이동
	//		if (NavPath->PathPoints.Num() == 0)
	//		{
	//			bMoveToDestination = false; // 모든 지점에 도착
	//		}
	//	}
	//	else
	//	{
	//		FVector Direction = (DestinationPoint - CurrentLocation).GetSafeNormal();
	//		AddMovementInput(Direction, 1.0f);
	//	}
	//
	//	// 디버그용으로 경로를 시각화
	//	for (const FVector& Point : NavPath->PathPoints) // 변경된 부분
	//	{
	//		DrawDebugSphere(GetWorld(), Point, 20.0f, 8, FColor::Red, false, -1.0f, 0, 2.0f); // 변경된 부분
	//	}
	//}

	if (bMoveToDestination && PathPoints.Num() > 0)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector DestinationPoint = PathPoints[0];

		float Distance = FVector::Dist(CurrentLocation, DestinationPoint);

		if (Distance < 100.0f) // 목표 지점에 도착했는지 확인
		{
			PathPoints.RemoveAt(0); // 다음 지점으로 이동
			if (PathPoints.Num() == 0)
			{
				bMoveToDestination = false; // 모든 지점에 도착
			}
		}
		else
		{
			FVector Direction = (DestinationPoint - CurrentLocation).GetSafeNormal();
			AddMovementInput(Direction, 2.0f);
		}

		// 디버그용으로 경로를 시각화
		for (int32 i = 1; i < PathPoints.Num(); ++i)
		{
			DrawDebugLine(
				GetWorld(),
				PathPoints[i - 1],
				PathPoints[i],
				FColor::Red,
				false,
				-1.0f,
				0,
				2.0f
			);
		}
	}
}

void AMainPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerCharacter, Destination);
	DOREPLIFETIME(AMainPlayerCharacter, bMoveToDestination);
	DOREPLIFETIME(AMainPlayerCharacter, PathPoints);
	DOREPLIFETIME(AMainPlayerCharacter, mState);
}