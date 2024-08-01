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

//public:
//	virtual ADefaultPlayerState* GetPlayerState() const;

public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* NormalAttackMontage;

	virtual void NormalAttack(const APawn* InTarget);

	virtual void QSkill();

	void NormalAttackHitCheck(float Radius = 100.f, float Height = 100.f);

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
