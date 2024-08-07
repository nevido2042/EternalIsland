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

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"

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

DECLARE_LOG_CATEGORY_EXTERN(EI, Log, All);

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))

// %s : 문자열을 받아서 그 문자열을 채워준다.
// %s는 FString을 바로 주면 안 된다. 앞에 *를 붙여서 FString의 주소를 넘기면
// 있는 문자열 주소를 따라가 문자열 자체를 넘겨주면 된다.
// %d : 정수를 받아서 그 자리에 정수를 문자열로 변환하여 채워준다.
// %f : 실수를 받아서 그 자리에 실수를 문자열로 변환하여 채워준다.
#define LOG(Format, ...) UE_LOG(EI, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define LOGSTRING(str) UE_LOG(EI, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *str)

USTRUCT()
struct FJoinInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FString		ID;
	FString		Password;
	bool		Login;
};

UENUM()
enum class EServerType : uint32
{
	Login,
	TestMap
};


enum class EPacketHeader
{
	SessionType,

	// Unreal -> Relay
	PlayerInfo_Send,

	// Relay -> Unreal
	PlayerInfo_Receive,

	// Level Transition
	LevelTransition
};

UCLASS()
class EI_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};

