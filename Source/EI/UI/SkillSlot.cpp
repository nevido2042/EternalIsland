// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillSlot.h"
#include "Components/ProgressBar.h"

void USkillSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void USkillSlot::UpdateCoolTimeBar(float Value)
{
	CoolTimeBar->SetPercent(Value);
}
