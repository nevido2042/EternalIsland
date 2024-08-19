// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MeleePlayerCharacter.h"
#include "Projectile/Projectile.h"

AMeleePlayerCharacter::AMeleePlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

    AttackRange = 200.f;
    AttackSpeed = 1.f;

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(RootComponent);
    ParticleSystemComponent->SetAutoActivate(false);
    ParticleSystemComponent->SetIsReplicated(true);
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
    Super::QSkill();

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

void AMeleePlayerCharacter::WSkill()
{
    Super::WSkill();
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
}

void AMeleePlayerCharacter::ESkill(const FVector& ClickLocation)
{
    Super::ESkill(ClickLocation);

    MulticastActiveSystem();

    SetActorLocation(ClickLocation);
}

void AMeleePlayerCharacter::MulticastActiveSystem_Implementation()
{
    ParticleSystemComponent->ActivateSystem();
}
