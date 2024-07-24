// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMap/TestMapPC.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ATestMapPC::BeginPlay()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameOnly());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void ATestMapPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ATestMapPC::MoveToClickPoint);
	}
}

void ATestMapPC::MoveToClickPoint()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GetClickLocation());
}

FVector ATestMapPC::GetClickLocation()
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
