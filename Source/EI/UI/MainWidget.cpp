// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainWidget.h"
#include "UI/HPBar.h"

void UMainWidget::UpdateHPBar(float Value)
{
	UHPBar* HPBar = Cast<UHPBar>(mHPBar);
	HPBar->UpdateHPBar(Value);
}
