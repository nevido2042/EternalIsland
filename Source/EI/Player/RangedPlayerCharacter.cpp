// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RangedPlayerCharacter.h"

void ARangedPlayerCharacter::NormalAttack()
{
	LookAtMousePos();
	PlayAnimMontage(NormalAttackMontage);
	NormalAttackHitCheck(50.f, 500.f);
}
