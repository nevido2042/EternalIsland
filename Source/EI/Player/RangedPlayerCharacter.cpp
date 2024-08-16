// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedPlayerCharacter.h"
#include "DefaultPlayerController.h"
#include "NiagaraComponent.h"

ARangedPlayerCharacter::ARangedPlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AttackRange = 500.f;
    AttackSpeed = 2.f;

    bReplicates = true;

    /*NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(RootComponent);*/

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(RootComponent);
    ParticleSystemComponent->SetIsReplicated(true);
}

void ARangedPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARangedPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARangedPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    //GetWorld()->SpawnActor<AActor>(Projectile, GetActorLocation(), GetActorRotation());
    //NiagaraComponent->ActivateSystem();

    //NiagaraComponent->SetNiagaraVariableFloat("User.SimulationSpeed", 3.f);
    //NiagaraComponent->SetNiagaraVariableFloat("User.PlaybackRate", 3.f);
    //NiagaraComponent->SetNiagaraVariableFloat(TEXT("User.SimulationSpeed"), 3.f);

}

void ARangedPlayerCharacter::NormalAttack(APawn* InTarget)
{
    Super::NormalAttack(InTarget);
}

void ARangedPlayerCharacter::QSkill()
{
    Super::QSkill();

    UE_LOG(LogTemp, Log, TEXT("QSkill"));

    CapsuleHitCheck(50.f, 500.f);

    /*MulticastActiveSystem();*/
}

void ARangedPlayerCharacter::WSkill()
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

void ARangedPlayerCharacter::ESkill(const FVector& ClickLocation)
{
    Super::ESkill(ClickLocation);

    MulticastActiveSystem();

    SetActorLocation(ClickLocation);
}

void ARangedPlayerCharacter::MulticastActiveSystem_Implementation()
{
    ParticleSystemComponent->ActivateSystem();

    /*NiagaraComponent->ReinitializeSystem();

    NiagaraComponent->SetWorldLocation(GetActorLocation());

    FRotator NewRotator(0.f, GetActorRotation().Yaw - 90.f, 0.f);
    NiagaraComponent->SetRelativeRotation(NewRotator);
    NiagaraComponent->ActivateSystem();*/
}

