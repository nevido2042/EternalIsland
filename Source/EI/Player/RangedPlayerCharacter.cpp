// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedPlayerCharacter.h"
#include "DefaultPlayerController.h"

ARangedPlayerCharacter::ARangedPlayerCharacter()
{
    AttackRange = 500.f;
    AttackSpeed = 2.f;
}

//void ARangedPlayerCharacter::BeginPlay()
//{
//
//    //GetWorld()->SpawnActor<AActor>(Projectile, GetActorLocation(), GetActorRotation());
//
//}

void ARangedPlayerCharacter::NormalAttack(APawn* InTarget)
{
    Super::NormalAttack(InTarget);
}

void ARangedPlayerCharacter::QSkill()
{
    Super::QSkill();

    UE_LOG(LogTemp, Log, TEXT("QSkill"));

    CapsuleHitCheck(50.f, 500.f);
    //GetWorld()->SpawnActor(Projectile);
}

void ARangedPlayerCharacter::WSkill()
{
    if (NormalAttackMontage)
    {
        MulticastPlayAttackMontage(NormalAttackMontage);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NormalAttackMontage is not set"));
    }
   
    //SpawnProjecttile();

    GetWorld()->SpawnActor<AActor>(Projectile, GetActorLocation(), GetActorRotation());


    //CapsuleHitCheck(50.f, 500.f);
    //GetWorld()->SpawnActor(Projectile);
}

//void ARangedPlayerCharacter::SpawnProjecttile_Implementation()
//{
//
//    GetWorld()->SpawnActor<AActor>(Projectile, GetActorLocation(), GetActorRotation());
//
//}
