// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
void AMainPlayerCharacter::NormalAttack()
{
	//NormalAttackHitCheck();
}

void AMainPlayerCharacter::QSkill()
{
}

void AMainPlayerCharacter::NormalAttackHitCheck(float Radius , float Height)
{
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
		false												// 지속적으로 드로우 (true면 지속적으로, false면 한 번만)
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


}

void AMainPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerCharacter, mState);
}