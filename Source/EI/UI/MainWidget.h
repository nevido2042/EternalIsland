// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class EI_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUserWidget* mHPBar;	
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USkillSlot* ESkillSlot;

public:
	void UpdateHPBar(float Value);
	void UpdateESkillCoolTimeBar(float Value);

};
