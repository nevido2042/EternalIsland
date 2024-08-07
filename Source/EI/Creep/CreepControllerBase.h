// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreepControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ACreepControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
