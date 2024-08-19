// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MeleePlayerCharacter.h"

AMeleePlayerCharacter::AMeleePlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC'"));

    if (MeshAsset.Succeeded())
    {
        // ������ �ҷ��� SkeletalMesh�� Character Ŭ������ ������ �ִ�
        // SkeletalMeshComponent�� �������ش�.
        GetMesh()->SetSkeletalMesh(MeshAsset.Object);
    }

    mJob = EPlayerJob::Swordsman;

    bReplicates = true;

    AttackRange = 200.f;
    AttackSpeed = 1.f;
}

void AMeleePlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMeleePlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMeleePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMeleePlayerCharacter::NormalAttack(APawn* InTarget)
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

    CapsuleHitCheck(200.f, 200.f);
    //GetWorld()->SpawnActor(Projectile);
}
