// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"
#include "DefaultPlayerState.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
}

void AMainPlayerCharacter::NomalAttack()
{
	NomalAttackHitCheck();
}

void AMainPlayerCharacter::NomalAttackHitCheck()
{
	FHitResult result;
	FCollisionQueryParams param(NAME_None, false, this);

	FVector StartLoc = GetActorLocation();
	StartLoc.Z += 100.f;

	FVector EndLoc = StartLoc + GetActorForwardVector() * 50;

	GetWorld()->SweepSingleByChannel(
		result,
		StartLoc, EndLoc,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeCapsule(100.f, 100.f), param);

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

	ADefaultPlayerState* targetState = targetCharacter->GetPlayerState<ADefaultPlayerState>();
	if (!IsValid(targetState))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack - targetState Is Not Valid"));
		return;
	}

	targetState->InflictDamage(mState->GetAttackDamage(), result.ImpactNormal);
	UE_LOG(LogTemp, Warning, TEXT("Hit Successe"));
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

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	mState = GetPlayerState<ADefaultPlayerState>();
}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

