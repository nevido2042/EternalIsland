// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginMap/LoginMapPC.h"

void ALoginMapPC::BeginPlay()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());
}
