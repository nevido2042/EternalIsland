// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ASelectPlayerController : public APlayerController
{
	GENERATED_BODY()
	


public:
	ASelectPlayerController();

protected:
	TSubclassOf<UUserWidget> mSelectUIClass;
	class UCharacterSelectWidget* mSelectUIWidget;

	//UPROPERTY(ReplicatedUsing = OnRep_SelectJob)
	EPlayerJob	mSelectJob;

	FString		mID;

public:
	void SetID(const FString& ID)
	{
		mID = ID;
	}

	const FString& GetID()
	{
		return mID;
	}
//public:
//	UFUNCTION()
//	void OnRep_SelectJob();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Returns the properties used for network replication, this needs to be overridden by all actor classes with native replicated properties */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void MousePick();
	void PickCharacter();

//private:
//	// Reliable, UnReliable
//	UFUNCTION(BlueprintCallable, Server, Reliable)
//	void SendSelectJob(EPlayerJob Job);
//	void SendSelectJob_Implementation(EPlayerJob Job);

};
