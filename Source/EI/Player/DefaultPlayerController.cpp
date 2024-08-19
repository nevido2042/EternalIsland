// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "MainPlayerCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "UI/GraphicsSettings.h"
#include "UI/MainWidget.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	CachedDestination = FVector::ZeroVector;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bReplicates = true;
}

void ADefaultPlayerController::OnPossess(APawn* InPawn)
{
	// 초기화
	Super::OnPossess(InPawn);
	ControlledPawn = InPawn;
	ControlledCharacter = Cast<AMainPlayerCharacter>(InPawn);

	AttackSpeed = ControlledCharacter->GetAttackSpeed();

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

//void ADefaultPlayerController::ClientLevelTransition_Implementation(EServerType Type)
//{
//	// 레벨을 전환한다.
//	FString	Option = FString::Printf(TEXT("Job=%d?ID=%s"), (int32)mJob,
//		*GetID());
//
//	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
//		FString::Printf(TEXT("Option : %s ServerType : %d"),
//			*Option, (int32)Type));
//
//	switch (Type)
//	{
//	case EServerType::Login:
//		break;
//	case EServerType::Select:
//		break;
//	case EServerType::Main:
//		UGameplayStatics::OpenLevel(GetWorld(), TEXT("192.168.0.118:10002"), true, Option);
//		break;
//	}
//}
//
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
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnSetDestination);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnSetDestination);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnSetDestination);
		
		//평타
		EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnNormalAttackClicked);

		//스킬 발동
		EnhancedInputComponent->BindAction(ActiveSkillAction, ETriggerEvent::Started, this, &ADefaultPlayerController::OnActiveSkillClicked);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnAttackTriggered);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnAttackReleased);
		//EnhancedInputComponent->BindAction(SetAttackAction, ETriggerEvent::Canceled, this, &ADefaultPlayerController::OnAttackReleased);
	
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
	FVector ClickLocation = GetMouseLocation();
	MoveToLocation(ClickLocation);
}

void ADefaultPlayerController::MoveToLocation(const FVector Location)
{
	if (!GetCharacter())
	{
		return;
	}

	if (GetCharacter()->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		return;
	}

	Target = Cast<APawn>(GetClickActor());


	ServerMoveToLocation(Location);


}

void ADefaultPlayerController::OnNormalAttackClicked()
{
	Target = Cast<APawn>(GetClickActor());

	if (!Target|| Target == GetPawn())
	{
		ClearTimer();
		return;
	}

	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "CheckTargetDist", Target);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CheckTargetDist, Delegate, 0.1f, true, 0.f);

	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
		TEXT("OnNormalAttackClicked"));
	LOG(TEXT("OnNormalAttackClicked"));
}

void ADefaultPlayerController::OnActiveSkillClicked()
{
	if (SelectSkill == ESkill::NONE)
		return;
	UE_LOG(LogTemp, Log, TEXT("OnActiveSkillClicked"));
	StopMovement();

	ActiveSkill(SelectSkill);
}


void ADefaultPlayerController::OnFirstSkillClicked()
{
	SelectSkill = ESkill::Q;
	UE_LOG(LogTemp, Log, TEXT("OnFirstSkillClicked"))
	//StopMovement();
}

void ADefaultPlayerController::OnSecondSkillClicked()
{
	SelectSkill = ESkill::W;
	//StopMovement();
}

void ADefaultPlayerController::OnThirdSkillClicked()
{
	SelectSkill = ESkill::E;
	//StopMovement();
}

void ADefaultPlayerController::ActiveSkill(ESkill InSkill)
{
	FVector ClickLocation = GetMouseLocation();
	if (GetWorld()->GetNetMode() == ENetMode::NM_Client)
	{
		ControlledCharacter->LookAtMousePos(ClickLocation);
	}

	switch (InSkill)
	{
	case ESkill::NONE:
		break;
	case ESkill::Q:
	{
		ServerQSkill(ClickLocation);
		break;
	}
	case ESkill::W:
	{
		ServerWSkill(ClickLocation);
		break;
	}
		
	case ESkill::E:
	{
		ServerESkill(ClickLocation);
		break;
	}
	default:
		break;
	}

	SelectSkill = ESkill::NONE;
}


void ADefaultPlayerController::CheckTargetDist(APawn* InTarget)
{
	if (!GetPawn())
	{
		return;
	}

	//사거리를 체크해서 추적할지 공격할지 판단
	float AttackRange;
	AttackRange = Cast<AMainPlayerCharacter>(GetPawn())->GetAttackRange();

	float Dist = FVector::Dist(GetPawn()->GetActorLocation(), InTarget->GetActorLocation());
	if (Dist > AttackRange)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_NormalAttack);

		MoveToLocation(InTarget->GetActorLocation());

		return;
	}


	if (GetWorld()->GetTimerManager().TimerExists(TimerHandle_NormalAttack))
	{
		return;
	}


	//WaitTime = AttackSpeed - (현재시간 - 마지막에 공격했던 시간)
	float WaitTime = AttackSpeed - (GetWorld()->GetTimeSeconds() - LastAttackTime);

	if (WaitTime < 0.f)
	{
		StopMovement();
		WaitTime = 0.f;
	}

	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "ServerNormalAttack", InTarget);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_NormalAttack, Delegate, AttackSpeed, true, WaitTime);

	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
		TEXT("CheckTargetDist"));
	LOG(TEXT("CheckTargetDist"));
}

void ADefaultPlayerController::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_NormalAttack);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CheckTargetDist);
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

	if (GraphicSettingWidgetAsset)
	{
		GraphicSettingWidget = CreateWidget(GetWorld(), GraphicSettingWidgetAsset);
		GraphicSettingWidget->AddToViewport();
	}

	if (MainWidgetAsset)
	{
		UUserWidget* UserWidget = CreateWidget(GetWorld(), MainWidgetAsset);
		if (UserWidget)
		{
			MainWidget = Cast<UMainWidget>(UserWidget);

			if (MainWidget)
			{
				MainWidget->AddToViewport();
			}
		}
		
		
	}
}

void ADefaultPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADefaultPlayerController::ServerMoveToLocation_Implementation(const FVector& DestLocation)
{	
	AMainPlayerCharacter* MyCharacter = Cast<AMainPlayerCharacter>(GetPawn());
	if (MyCharacter)
	{
		// 서버에서 캐릭터 이동을 처리
		MyCharacter->MoveToLocation(DestLocation);
	}
	MulticastSpawnFX(DestLocation);
}

bool ADefaultPlayerController::ServerMoveToLocation_Validate(const FVector& DestLocation)
{
	return true;
}


void ADefaultPlayerController::MulticastSpawnFX_Implementation(const FVector& Location)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}


void ADefaultPlayerController::ServerNormalAttack_Implementation(APawn* InTarget)
{
	if (!InTarget)
	{
		return;
	}

	const FVector TargetLocation = InTarget->GetTargetLocation();

	UE_LOG(LogTemp, Log, TEXT("ServerNormalAttack called on server"));
	UE_LOG(LogTemp, Log, TEXT("TargetLocation on server: %s"), *TargetLocation.ToString());

	if (ControlledCharacter)
	{
		StopMovement();
		ControlledCharacter->LookAtMousePos(TargetLocation);
		ControlledCharacter->NormalAttack(InTarget);
		MulticastNormalAttack(TargetLocation);
	}
}

bool ADefaultPlayerController::ServerNormalAttack_Validate(const APawn* InTarget)
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

		LastAttackTime = GetWorld()->GetTimeSeconds();
	}
}

void ADefaultPlayerController::ServerQSkill_Implementation(const FVector& ClickLocation)
{
	UE_LOG(LogTemp, Log, TEXT("ServerQSkill called on server"));
	UE_LOG(LogTemp, Log, TEXT("ClickLocation on server: %s"), *ClickLocation.ToString());
	if (ControlledCharacter)
	{
		ControlledCharacter->LookAtMousePos(ClickLocation);

		ClientQSkill(ClickLocation); // 클라이언트에서도 스킬 발사 효과 적용
		ControlledCharacter->QSkill();

	}
}

bool ADefaultPlayerController::ServerQSkill_Validate(const FVector& ClickLocation)
{
	return true;
}


void ADefaultPlayerController::ClientQSkill_Implementation(const FVector& ClickLocation)
{
	if (ControlledCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("MulticastQSkill called on client"));
		ControlledCharacter->LookAtMousePos(ClickLocation);
	}
}

FVector ADefaultPlayerController::GetMouseLocation()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	// If we hit a surface, cache the location
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	return bHitSuccessful ? Hit.Location : FVector::ZeroVector;
}

AActor* ADefaultPlayerController::GetClickActor()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	// If we hit a surface, cache the location
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		return Hit.GetActor();
	}
	else
	{
		return nullptr;
	}
}

void ADefaultPlayerController::ServerWSkill_Implementation(const FVector& ClickLocation)
{
	UE_LOG(LogTemp, Log, TEXT("ServerWSkill called on server"));
	UE_LOG(LogTemp, Log, TEXT("ClickLocation on server: %s"), *ClickLocation.ToString());
	if (ControlledCharacter)
	{
		StopMovement();
		ControlledCharacter->LookAtMousePos(ClickLocation);
		ControlledCharacter->WSkill();
	}
}

bool ADefaultPlayerController::ServerWSkill_Validate(const FVector& ClickLocation)
{
	return true;
}

void ADefaultPlayerController::ServerESkill_Implementation(const FVector& ClickLocation)
{
	UE_LOG(LogTemp, Log, TEXT("ServerESkill called on server"));
	UE_LOG(LogTemp, Log, TEXT("ClickLocation on server: %s"), *ClickLocation.ToString());
	if (ControlledCharacter)
	{
		StopMovement();
		ControlledCharacter->LookAtMousePos(ClickLocation);
		ControlledCharacter->ESkill(ClickLocation);
	}
}

bool ADefaultPlayerController::ServerESkill_Validate(const FVector& ClickLocation)
{
	return true;
}

void ADefaultPlayerController::ClientWSkill_Implementation(const FVector& ClickLocation)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->LookAtMousePos(ClickLocation);
	}
}

void ADefaultPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefaultPlayerController, mID);
	DOREPLIFETIME(ADefaultPlayerController, mJob);
}