// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HPBar.h"
#include "Components/ProgressBar.h"

void UHPBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UpdateHPBar(1.f);
}

void UHPBar::UpdateHPBar(float Value)
{
	HPBar->SetPercent(Value);
}
