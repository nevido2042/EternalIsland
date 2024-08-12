// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GraphicsSettings.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UGraphicsSettings::NativeConstruct()
{
    Super::NativeConstruct();

    if (ResolutionSlider)
    {
        ResolutionSlider->OnValueChanged.AddDynamic(this, &UGraphicsSettings::OnResolutionSliderValueChanged);
    }

    if (ShadowQualityDropdown)
    {
        ShadowQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnShadowQualitySelectionChanged);
    }

    if (TextureQualityDropdown)
    {
        TextureQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnTextureQualitySelectionChanged);
    }

    if (ReflectionQualityDropdown)
    {
        ReflectionQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnReflectionQualitySelectionChanged);
    }

    if (AntiAliasingCheckbox)
    {
        AntiAliasingCheckbox->OnCheckStateChanged.AddDynamic(this, &UGraphicsSettings::OnAntiAliasingCheckboxChanged);
    }

    if (PostProcessingCheckbox)
    {
        PostProcessingCheckbox->OnCheckStateChanged.AddDynamic(this, &UGraphicsSettings::OnPostProcessingCheckboxChanged);
    }
}

void UGraphicsSettings::OnResolutionSliderValueChanged(float Value)
{
    FString Command = FString::Printf(TEXT("r.ScreenPercentage %f"), Value * 100.0f); // 0.0 to 1.0 scale to 0 to 100
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnShadowQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    int32 QualityLevel = 0;
    if (SelectedItem == TEXT("Low"))
    {
        QualityLevel = 0;
    }
    else if (SelectedItem == TEXT("Medium"))
    {
        QualityLevel = 1;
    }
    else if (SelectedItem == TEXT("High"))
    {
        QualityLevel = 2;
    }
    FString Command = FString::Printf(TEXT("r.ShadowQuality %d"), QualityLevel);
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnTextureQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    int32 QualityLevel = 0;
    if (SelectedItem == TEXT("Low"))
    {
        QualityLevel = 0;
    }
    else if (SelectedItem == TEXT("Medium"))
    {
        QualityLevel = 1;
    }
    else if (SelectedItem == TEXT("High"))
    {
        QualityLevel = 2;
    }
    FString Command = FString::Printf(TEXT("r.Streaming.PoolSize %d"), QualityLevel * 1000); // Adjust pool size for demonstration
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnReflectionQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    int32 QualityLevel = 0;
    if (SelectedItem == TEXT("Low"))
    {
        QualityLevel = 0;
    }
    else if (SelectedItem == TEXT("Medium"))
    {
        QualityLevel = 1;
    }
    else if (SelectedItem == TEXT("High"))
    {
        QualityLevel = 2;
    }
    FString Command = FString::Printf(TEXT("r.ReflectQuality %d"), QualityLevel);
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnAntiAliasingCheckboxChanged(bool bIsChecked)
{
    FString Command = bIsChecked ? TEXT("r.PostProcessAAQuality 2") : TEXT("r.PostProcessAAQuality 0");
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnPostProcessingCheckboxChanged(bool bIsChecked)
{
    FString Command = bIsChecked ? TEXT("r.PostProcessing 1") : TEXT("r.PostProcessing 0");
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}
