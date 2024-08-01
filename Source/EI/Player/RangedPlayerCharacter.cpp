// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedPlayerCharacter.h"
#include "DefaultPlayerController.h"

ARangedPlayerCharacter::ARangedPlayerCharacter()
{
    AttackRange = 500.f;
}

void ARangedPlayerCharacter::NormalAttack(const APawn* InTarget)
{
    Super::NormalAttack(InTarget);
}

void ARangedPlayerCharacter::QSkill()
{
    if (NormalAttackMontage)
    {
        MulticastPlayAttackMontage(NormalAttackMontage);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NormalAttackMontage is not set"));
    }

    NormalAttackHitCheck(50.f, 500.f);
    //GetWorld()->SpawnActor(Projectile);
}
