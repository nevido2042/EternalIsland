// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class EI_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UButton* mStartButton;

public:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void StartClick();

	void EnableStartButton(bool Enable);
};
