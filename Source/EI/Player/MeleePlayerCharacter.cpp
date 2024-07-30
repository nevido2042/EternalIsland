// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MeleePlayerCharacter.h"

void AMeleePlayerCharacter::NormalAttack()
{
    //PlayAnimMontage(NormalAttackMontage);
    if (NormalAttackMontage)
    {
        MulticastPlayAttackMontage(NormalAttackMontage);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NormalAttackMontage is not set"));
    }
    NormalAttackHitCheck(100.f, 100.f);
}
