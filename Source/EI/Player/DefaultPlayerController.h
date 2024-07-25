// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DefaultPlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class EI_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADefaultPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	double MinMoveDistanceThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	TObjectPtr<APawn> ControlledPawn;

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetFirstSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetSecondSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetThirdSkillAction;


public:

	virtual void EnableInput(class APlayerController* PlayerController) override;
	virtual void DisableInput(class APlayerController* PlayerController) override;

	FVector GetPointTargetLocation()
	{
		return CachedDestination;
	}

	FVector GetClickLocation();

protected:
	/** Input handlers for SetDestination action. */
	///void OnInputStarted();
	UFUNCTION()
	void OnSetDestinationStarted();
	UFUNCTION()
	void OnSetDestinationTriggered();
	UFUNCTION()
	void OnSetDestinationReleased();

	void OnAttackClicked();
	void OnAttackTriggered();
	void OnAttackReleased();

	void OnFirstSkillClicked();
	void OnSecondSkillClicked();
	void OnThirdSkillClicked();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	virtual void SetupInputComponent() override;



	// To add mapping context
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FVector CachedDestination;
};
