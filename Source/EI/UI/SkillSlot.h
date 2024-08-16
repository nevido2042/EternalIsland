// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class EI_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* CoolTimeBar;

	virtual void NativeOnInitialized();

public:
	void UpdateCoolTimeBar(float Value);
};
