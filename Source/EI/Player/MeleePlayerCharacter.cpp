// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MeleePlayerCharacter.h"

AMeleePlayerCharacter::AMeleePlayerCharacter()
{
    AttackRange = 100.f;
}

void AMeleePlayerCharacter::NormalAttack(const APawn* InTarget)
{
	Super::NormalAttack(InTarget);
}

void AMeleePlayerCharacter::QSkill()
{
    if (NormalAttackMontage)
    {
        MulticastPlayAttackMontage(NormalAttackMontage);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NormalAttackMontage is not set"));
    }

    NormalAttackHitCheck(200.f, 200.f);
    //GetWorld()->SpawnActor(Projectile);
}
