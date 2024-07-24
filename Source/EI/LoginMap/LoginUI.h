// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUI.generated.h"

/**
 * 
 */

class UButton;
class UEditableTextBox;

UCLASS()
class EI_API ULoginUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Meta = (BindWidget))
	UButton* CreateServerBtn;

	UPROPERTY(Meta = (BindWidget))
	UButton* JoinServerBtn;

	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* IPTextBox;

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void CreateServerHandler();
	UFUNCTION()
	void JoinServerHandler();
	UFUNCTION()
	void OnIPBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
