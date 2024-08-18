// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Character.h"
#include "DefaultPlayerState.h"
#include "MainPlayerCharacter.generated.h"

UCLASS()
class EI_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayerCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const
	{
		return TopDownCameraComponent;
	}

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}

	ADefaultPlayerState* GetCharacterState()
	{
		return mState;
	}


protected:
	float AttackRange = 500.f;
	float AttackSpeed = 1.f;
	EPlayerJob		mJob;

public:
	void SetPlayerInfo(EPlayerJob Job)
	{
		mJob = Job;
	}
public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SendPlayerInfo(EServerType Type);
	void SendPlayerInfo_Implementation(EServerType Type);
protected:
	FTimerHandle CooldownTimerHandle;
	float ESkillCoolTime = 3.0f;
	float RemainESkillCoolTime;
	bool bIsCooldownActive = false;
protected:
	UFUNCTION()
	void UpdateCooldown();
	UFUNCTION()
	void OnCooldownComplete();

	void StartCooldown();

public:
	float GetAttackRange() { return AttackRange; }
	float GetAttackSpeed() { return AttackSpeed; }
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* NormalAttackMontage;

	virtual void NormalAttack(APawn* InTarget);

	virtual void QSkill();

	virtual void WSkill();

	virtual void ESkill(const FVector& ClickLocation);

	void CapsuleHitCheck(float Radius = 100.f, float Height = 100.f);

	void LookAtMousePos(const FVector& TargetLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayAttackMontage(UAnimMontage* Montage);
	void MulticastPlayAttackMontage_Implementation(UAnimMontage* Montage);

public:
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

	void InflictDamageTo(FHitResult result, float Multiplier = 1.0F);

	void DrawNomalAttackDebug(FVector CenterLocation, FQuat SocketRotation, AActor* HitActor);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	ADefaultPlayerState* mState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(Replicated)
	FVector Destination;

	UPROPERTY(Replicated)
	bool bMoveToDestination;


	UPROPERTY(ReplicatedUsing = OnRep_PathPoints)
	TArray<FVector> PathPoints;



	void MoveToLocation(const FVector& Location);

	void FollowPath(float DeltaTime);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_PathPoints();
};
