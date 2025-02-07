// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainWidget.h"
#include "UI/HPBar.h"
#include "UI/SkillSlot.h"

void UMainWidget::UpdateHPBar(float Value)
{
	UHPBar* HPBar = Cast<UHPBar>(mHPBar);
	HPBar->UpdateHPBar(Value);
}

void UMainWidget::UpdateESkillCoolTimeBar(float Value)
{
	if (IsValid(ESkillSlot))
	{
		USkillSlot* SkillSlot = Cast<USkillSlot>(ESkillSlot);
		if (SkillSlot)
		{
			//USkillSlot* SkillSlot = Cast<USkillSlot>(ESkillSlot);
			SkillSlot->UpdateCoolTimeBar(Value);
		}

	}

}
