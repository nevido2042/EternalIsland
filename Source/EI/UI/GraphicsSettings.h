// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsSettings.generated.h"

/**
 * 
 */
UCLASS()
class EI_API UGraphicsSettings : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

protected:
    // UI 요소들
    UPROPERTY(meta = (BindWidget))
    class USlider* ResolutionSlider;

    UPROPERTY(meta = (BindWidget))
    class UComboBoxString* ShadowQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    class UComboBoxString* TextureQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    class UComboBoxString* ReflectionQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox* AntiAliasingCheckbox;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox* PostProcessingCheckbox;

    // UI 이벤트 처리 함수들
    UFUNCTION()
    void OnResolutionSliderValueChanged(float Value);

    UFUNCTION()
    void OnShadowQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnTextureQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnReflectionQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnAntiAliasingCheckboxChanged(bool bIsChecked);

    UFUNCTION()
    void OnPostProcessingCheckboxChanged(bool bIsChecked);
};
