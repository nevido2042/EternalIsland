// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMap/TestMapPC.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ATestMapPC::BeginPlay()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,)
}
