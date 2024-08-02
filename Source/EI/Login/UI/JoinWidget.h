// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "JoinWidget.generated.h"

/**
 * 
 */
UCLASS()
class EI_API UJoinWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UEditableTextBox* mIDInput;
	UEditableTextBox* mPassInput;
	UButton* mJoinButton;
	UButton* mCancelButton;

public:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void JoinClick();

	UFUNCTION()
	void CancelClick();

	void JoinComplete(bool Join);

private:
	void ClearInput();
	bool IsEmptyInput();
};
