// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameInfo.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DefaultPlayerController.generated.h"

class UNiagaraSystem;

enum class ESkill :uint8
{
	NONE,
	Q,
	W,
	E
};

UCLASS()
class EI_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADefaultPlayerController();

	virtual void OnPossess(APawn* InPawn) override;

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

private:
	UPROPERTY()
	class AMainPlayerCharacter* ControlledCharacter;

protected:
	/** Input handlers for SetDestination action. */
	void OnInputStarted();

	void OnSetDestination();

	void OnAttackClicked();
	//void OnAttackTriggered();
	//void OnAttackReleased();

	void OnFirstSkillClicked();
	void OnSecondSkillClicked();
	void OnThirdSkillClicked();

	ESkill SelectSkill = ESkill::NONE;
	void ActiveSkill(ESkill InSkill);


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	virtual void SetupInputComponent() override;



	// To add mapping context
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FVector CachedDestination;


	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMoveToLocation(const FVector& DestLocation);
	void ServerMoveToLocation_Implementation(const FVector& DestLocation);
	bool ServerMoveToLocation_Validate(const FVector& DestLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastMoveToLocation(const FVector& DestLocation);
	void MulticastMoveToLocation_Implementation(const FVector& DestLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpawnFX(const FVector& Location);
	void MulticastSpawnFX_Implementation(const FVector& Location);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerLookAtMousePos(const FVector& TargetLocation);
	void ServerLookAtMousePos_Implementation(const FVector& TargetLocation);
	bool ServerLookAtMousePos_Validate(const FVector& TargetLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLookAtMousePos(const FVector& TargetLocation);
	void MulticastLookAtMousePos_Implementation(const FVector& TargetLocation);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerNormalAttack(const FVector& ClickLocation);
	void ServerNormalAttack_Implementation(const FVector& ClickLocation);
	bool ServerNormalAttack_Validate(const FVector& ClickLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastNormalAttack(const FVector& ClickLocation);
	void MulticastNormalAttack_Implementation(const FVector& ClickLocation);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerQSkill(const FVector& ClickLocation);
	void ServerQSkill_Implementation(const FVector& ClickLocation);
	bool ServerQSkill_Validate(const FVector& ClickLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastServerQSkill(const FVector& ClickLocation);
	void MulticastServerQSkill_Implementation(const FVector& ClickLocation);
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainWidgetAsset;
	UUserWidget* MainWidget;
public:
	UUserWidget* GetMainWidget() { return MainWidget; }
};
