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

protected:
	UPROPERTY(Replicated)
	FString		mID;

	UPROPERTY(Replicated)
	EPlayerJob	mJob;

public:
	void SetJob(EPlayerJob Job)
	{
		mJob = Job;
	}

	const FString& GetID()
	{
		return mID;
	}

	void SetID(const FString& ID)
	{
		mID = ID;
	}

	//UFUNCTION(BlueprintCallable, Client, Reliable)
	//void ClientLevelTransition(EServerType Type);
	//void ClientLevelTransition_Implementation(EServerType Type);


public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	//평타
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetAttackAction;

	//스킬 발동
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActiveSkillAction;

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

	FVector GetMouseLocation();
	AActor* GetClickActor();

private:
	UPROPERTY()
	class AMainPlayerCharacter* ControlledCharacter;

protected:
	/** Input handlers for SetDestination action. */
	void OnInputStarted();

	void OnSetDestination();

	void MoveToLocation(const FVector Location);

	void OnNormalAttackClicked();

	void OnActiveSkillClicked();
	//void OnAttackTriggered();
	//void OnAttackReleased();

	void OnFirstSkillClicked();
	void OnSecondSkillClicked();
	void OnThirdSkillClicked();

	ESkill SelectSkill = ESkill::NONE;
	void ActiveSkill(ESkill InSkill);

	APawn* Target;
	FTimerHandle TimerHandle_NormalAttack;
	FTimerHandle TimerHandle_CheckTargetDist;

	double LastAttackTime = -999.f;

	float AttackSpeed = 1.f;

	UFUNCTION()
	void CheckTargetDist(APawn* InTarget);

public:
	APawn* GetTarget() { return Target; }
	void ClearTimer();

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

	
	UFUNCTION(Client, Reliable)
	void MulticastSpawnFX(const FVector& Location);
	void MulticastSpawnFX_Implementation(const FVector& Location);



	UFUNCTION(Server, Reliable, WithValidation)
	void ServerNormalAttack(const APawn* InTarget);
	void ServerNormalAttack_Implementation(APawn* InTarget);
	bool ServerNormalAttack_Validate(const APawn* InTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastNormalAttack(const FVector& ClickLocation);
	void MulticastNormalAttack_Implementation(const FVector& ClickLocation);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerQSkill(const FVector& ClickLocation);
	void ServerQSkill_Implementation(const FVector& ClickLocation);
	bool ServerQSkill_Validate(const FVector& ClickLocation);

	UFUNCTION(Client, Reliable)
	void ClientQSkill(const FVector& ClickLocation);
	void ClientQSkill_Implementation(const FVector& ClickLocation);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerWSkill(const FVector& ClickLocation);
	void ServerWSkill_Implementation(const FVector& ClickLocation);
	bool ServerWSkill_Validate(const FVector& ClickLocation);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerESkill(const FVector& ClickLocation);
	void ServerESkill_Implementation(const FVector& ClickLocation);
	bool ServerESkill_Validate(const FVector& ClickLocation);

	UFUNCTION(Client, Reliable)
	void ClientWSkill(const FVector& ClickLocation);
	void ClientWSkill_Implementation(const FVector& ClickLocation);


public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainWidgetAsset;
	class UMainWidget* MainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GraphicSettingWidgetAsset;
	UUserWidget* GraphicSettingWidget;
public:
	class UMainWidget* GetMainWidget() { return MainWidget; }

protected:
	FTimerHandle QSkillTimerHandle;


};
