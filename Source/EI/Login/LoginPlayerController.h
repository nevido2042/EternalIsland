// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALoginPlayerController();

private:
	TSubclassOf<UUserWidget> mLoginUIClass;
	class ULoginWidget* mLoginUIWidget;

	UPROPERTY(ReplicatedUsing = OnRep_LoginSuccess)
	bool		mLoginSuccess;

	UPROPERTY(ReplicatedUsing = OnRep_JoinSuccess)
	bool		mJoinSuccess;

public:
	UFUNCTION()
	void OnRep_LoginSuccess();

	UFUNCTION()
	void OnRep_JoinSuccess();


protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Returns the properties used for network replication, this needs to be overridden by all actor classes with native replicated properties */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Reliable, UnReliable
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SendLoginInfo(const FText& ID, const FText& Password);
	void SendLoginInfo_Implementation(const FText& ID, const FText& Password);

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void SendClient(bool LoginSuccess, const FString& ID);
	void SendClient_Implementation(bool LoginSuccess, const FString& ID);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SendJoinInfo(const FText& ID, const FText& Password);
	void SendJoinInfo_Implementation(const FText& ID, const FText& Password);

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void SendJoinClient(bool JoinSuccess);
	void SendJoinClient_Implementation(bool JoinSuccess);

};
