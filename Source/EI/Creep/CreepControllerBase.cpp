// Fill out your copyright notice in the Description page of Project Settings.


#include "Creep/CreepControllerBase.h"
#include "Creep/CreepBase.h"

void ACreepControllerBase::BeginPlay()
{
	Super::BeginPlay();

	Cast<ACreepBase>(GetPawn())->ChangeState(EState::Wander);
}


