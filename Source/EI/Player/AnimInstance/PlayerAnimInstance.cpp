// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AnimInstance/PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Pawn = TryGetPawnOwner();
	if (!Pawn) { return; }

	MovementComponent = Pawn->GetMovementComponent();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Pawn) { return; }

	if (MovementComponent)
	{
		Speed = MovementComponent->Velocity.Length();
	}
}
