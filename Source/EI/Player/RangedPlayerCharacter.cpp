// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedPlayerCharacter.h"
#include "DefaultPlayerController.h"

ARangedPlayerCharacter::ARangedPlayerCharacter()
{
    AttackRange = 500.f;
    AttackSpeed = 2.f;

    bReplicates = true;
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

    if (NormalAttackMontage)
    {
        MulticastPlayAttackMontage(NormalAttackMontage);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NormalAttackMontage is not set"));
    }

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
   

    FTransform SpawnTransform;
    AProjectile* NewProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(Projectile, SpawnTransform);
    NewProjectile->SetOwnerActor(this);
    SpawnTransform.SetLocation(GetActorLocation());
    SpawnTransform.SetRotation(FQuat(GetActorRotation()));
    UGameplayStatics::FinishSpawningActor(NewProjectile, SpawnTransform);

    //CapsuleHitCheck(50.f, 500.f);
    //GetWorld()->SpawnActor(Projectile);
}

//void ARangedPlayerCharacter::SpawnProjecttile_Implementation()
//{
//
//    GetWorld()->SpawnActor<AActor>(Projectile, GetActorLocation(), GetActorRotation());
//
//}
