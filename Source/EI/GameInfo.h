// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "AIController.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"


#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

/**
 * 
 */
UCLASS()
class EI_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
