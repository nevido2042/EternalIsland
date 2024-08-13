#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "GraphicsSettings.generated.h"

/**
 * UGraphicsSettings는 게임의 그래픽 설정을 조정하는 UI를 관리합니다.
 */

class UComboBoxString;

UCLASS()
class EI_API UGraphicsSettings : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    // 드롭다운 위젯
    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ScreenModeDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ResolutionDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ShadowQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* TextureQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ReflectionQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ViewDistanceDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* GlobalIlluminationDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* AntiAliasingDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* EffectsQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* FoliageQualityDropdown;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ShadingQualityDropdown;

    // 이벤트 핸들러
    UFUNCTION()
    void OnScreenModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnShadowQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnTextureQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnReflectionQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnViewDistanceSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnGlobalIlluminationSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnAntiAliasingSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnEffectsQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnFoliageQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnShadingQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};
