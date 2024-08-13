// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "EIGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EI_API UEIGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UEIGameInstance();
	//~UEIGameInstance();

protected:
	EPlayerJob	mSelectJob;

public:
	void ChangeSelectJob(EPlayerJob Job)
	{
		mSelectJob = Job;
	}

	EPlayerJob GetSelectJob()	const
	{
		return mSelectJob;
	}

public:
	virtual void Init();

//protected:
//	virtual void FinishDestroy() override;
};
