// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JoinWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class EI_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IDInput;

	UEditableTextBox* mPassInput;
	UButton* mLoginButton;
	UButton* mJoinButton;
	UJoinWidget* mJoinWidget;

public:
	UJoinWidget* GetJoinWidget()	const
	{
		return mJoinWidget;
	}

public:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void LoginClick();

	UFUNCTION()
	void JoinClick();
};
