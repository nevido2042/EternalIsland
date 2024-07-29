// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "MainPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	CachedDestination = FVector::ZeroVector;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void ADefaultPlayerController::EnableInput(APlayerController* PlayerController)
{
	Super::EnableInput(this);
}
void ADefaultPlayerController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(this);

}
void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnSetDestinationStarted);
	
		EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnAttackClicked);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnAttackTriggered);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnAttackReleased);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Canceled, this, &ADefaultPlayerController::OnAttackReleased);
	
		EnhancedInputComponent->BindAction(SetFirstSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnFirstSkillClicked);
		EnhancedInputComponent->BindAction(SetSecondSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnSecondSkillClicked);
		EnhancedInputComponent->BindAction(SetThirdSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnThirdSkillClicked);
	}


}
//
//void ADefaultPlayerController::OnInputStarted()
//{
//	StopMovement();
//}

void ADefaultPlayerController::OnSetDestinationStarted()
{
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GetClickLocation());
	FVector ClickLocation = GetClickLocation();
	ServerMoveToLocation(ClickLocation);
}

void ADefaultPlayerController::OnSetDestinationTriggered()
{
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GetClickLocation());
	FVector ClickLocation = GetClickLocation();
	ServerMoveToLocation(ClickLocation);
}

void ADefaultPlayerController::OnSetDestinationReleased()
{

	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GetClickLocation());
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, GetClickLocation(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	FVector ClickLocation = GetClickLocation();
	ServerMoveToLocation(ClickLocation);
}

void ADefaultPlayerController::OnAttackClicked()
{
	Cast<AMainPlayerCharacter>(ControlledPawn)->NormalAttack();
}

//void ADefaultPlayerController::OnAttackTriggered()
//{
//	StopMovement();
//}
//
//void ADefaultPlayerController::OnAttackReleased()
//{
//	StopMovement();
//}
//
void ADefaultPlayerController::OnFirstSkillClicked()
{
	StopMovement();
}

void ADefaultPlayerController::OnSecondSkillClicked()
{
	StopMovement();
}

void ADefaultPlayerController::OnThirdSkillClicked()
{
	StopMovement();
}



void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = GetPawn();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}



}

void ADefaultPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADefaultPlayerController::ServerMoveToLocation_Implementation(const FVector& DestLocation)
{
	MulticastMoveToLocation(DestLocation);
	MulticastSpawnFX(DestLocation);
}

bool ADefaultPlayerController::ServerMoveToLocation_Validate(const FVector& DestLocation)
{
	return true;
}

void ADefaultPlayerController::MulticastMoveToLocation_Implementation(const FVector& DestLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
}

void ADefaultPlayerController::MulticastSpawnFX_Implementation(const FVector& Location)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

FVector ADefaultPlayerController::GetClickLocation()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		return Hit.Location;
	}

	return FVector::ZeroVector;
}

void ADefaultPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}