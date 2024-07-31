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
	class UUserWidget* mLoginUIWidget;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//Reliable, UnReliable 
	UFUNCTION(Server, Reliable)
	void SendLoginInfo(const FText& DI, const FText& Password);
	void SendLoginInfo_Implementation(const FText& DI, const FText& Password);
};
