// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "MainPlayerCharacter.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	CachedDestination = FVector::ZeroVector;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void ADefaultPlayerController::OnPossess(APawn* InPawn)
{
	// 초기화
	Super::OnPossess(InPawn);
	ControlledPawn = InPawn;
	ControlledCharacter = Cast<AMainPlayerCharacter>(InPawn);

	// 초기화 로그
	if (ControlledCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("ControlledCharacter initialized in OnPossess: %s"), *ControlledCharacter->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ControlledCharacter initialization failed in OnPossess"));
	}
}

void ADefaultPlayerController::EnableInput(APlayerController* PlayerController)
{
	Super::EnableInput(this);
}
void ADefaultPlayerController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(this);

}
void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnInputStarted);

		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnSetDestination);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnSetDestination);

		EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnAttackClicked);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnAttackTriggered);
	
		EnhancedInputComponent->BindAction(SetFirstSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnFirstSkillClicked);
		EnhancedInputComponent->BindAction(SetSecondSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnSecondSkillClicked);
		EnhancedInputComponent->BindAction(SetThirdSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnThirdSkillClicked);
	}


}

void ADefaultPlayerController::OnInputStarted()
{
	StopMovement();
}


void ADefaultPlayerController::OnSetDestination()
{
	FVector ClickLocation = GetClickLocation();
	if (ControlledCharacter)
	{
		ControlledCharacter->LookAtMousePos(ClickLocation);
	}
	ServerMoveToLocation(ClickLocation);
	ServerLookAtMousePos(ClickLocation);
}

void ADefaultPlayerController::OnAttackClicked()
{
	StopMovement();
	UE_LOG(LogTemp, Log, TEXT("OnAttackClicked called"));
	if (ControlledCharacter)
	{
		FVector ClickLocation = GetClickLocation();
		// 로그 출력: 클릭 위치 확인
		UE_LOG(LogTemp, Log, TEXT("ClickLocation: %s"), *ClickLocation.ToString());

		ServerNormalAttack(ClickLocation); // 서버에서 공격을 처리하도록 설정
	}
}


void ADefaultPlayerController::OnFirstSkillClicked()
{
	StopMovement();
}

void ADefaultPlayerController::OnSecondSkillClicked()
{
	StopMovement();
}

void ADefaultPlayerController::OnThirdSkillClicked()
{
	StopMovement();
}



void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledCharacter = Cast<AMainPlayerCharacter>(GetPawn());  // ControlledCharacter 초기화

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (MainWidgetAsset)
	{
		MainWidget = CreateWidget(GetWorld(), MainWidgetAsset);
		MainWidget->AddToViewport();
	}
}

void ADefaultPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADefaultPlayerController::ServerMoveToLocation_Implementation(const FVector& DestLocation)
{
	MulticastMoveToLocation(DestLocation);
	MulticastSpawnFX(DestLocation);
}

bool ADefaultPlayerController::ServerMoveToLocation_Validate(const FVector& DestLocation)
{
	return true;
}

void ADefaultPlayerController::MulticastMoveToLocation_Implementation(const FVector& DestLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
}

void ADefaultPlayerController::MulticastSpawnFX_Implementation(const FVector& Location)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void ADefaultPlayerController::ServerLookAtMousePos_Implementation(const FVector& TargetLocation)
{
	MulticastLookAtMousePos(TargetLocation);
}

bool ADefaultPlayerController::ServerLookAtMousePos_Validate(const FVector& TargetLocation)
{
	return true;
}

void ADefaultPlayerController::MulticastLookAtMousePos_Implementation(const FVector& TargetLocation)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->LookAtMousePos(TargetLocation);
	}

}

void ADefaultPlayerController::ServerNormalAttack_Implementation(const FVector& ClickLocation)
{

	UE_LOG(LogTemp, Log, TEXT("ServerNormalAttack called on server"));
	UE_LOG(LogTemp, Log, TEXT("ClickLocation on server: %s"), *ClickLocation.ToString());
	if (ControlledCharacter)
	{
		StopMovement();
		ControlledCharacter->LookAtMousePos(ClickLocation);
		ControlledCharacter->NormalAttack();
		MulticastNormalAttack(ClickLocation);
	}
}

bool ADefaultPlayerController::ServerNormalAttack_Validate(const FVector& ClickLocation)
{

	return true;
}

void ADefaultPlayerController::MulticastNormalAttack_Implementation(const FVector& ClickLocation)
{
	if (ControlledCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("MulticastNormalAttack called on client/server"));
		ControlledCharacter->LookAtMousePos(ClickLocation);
		//ControlledCharacter->NormalAttack();
	}
}

FVector ADefaultPlayerController::GetClickLocation()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	// If we hit a surface, cache the location
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return bHitSuccessful ? Hit.Location : FVector::ZeroVector;
	/*if (bHitSuccessful)
	{
		return Hit.Location;
	}

	return FVector::ZeroVector;*/
}



void ADefaultPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}