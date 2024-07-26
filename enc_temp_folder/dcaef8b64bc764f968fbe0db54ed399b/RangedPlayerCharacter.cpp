// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RangedPlayerCharacter.h"

void ARangedPlayerCharacter::NomalAttack()
{
	PlayAnimMontage(NormalAttackMontage);
	Super::NomalAttack();
}
