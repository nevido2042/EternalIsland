#include "UI/GraphicsSettings.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicsSettings::NativeConstruct()
{
    // ScreenModeDropdown 항목 추가 및 바인딩
    if (ScreenModeDropdown)
    {
        ScreenModeDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnScreenModeSelectionChanged);

        ScreenModeDropdown->AddOption(TEXT("Fullscreen"));
        ScreenModeDropdown->AddOption(TEXT("Windowed"));
        ScreenModeDropdown->AddOption(TEXT("Windowed Fullscreen"));

        ScreenModeDropdown->SetSelectedOption(TEXT("Windowed"));  // 기본 선택
    }

    // ResolutionDropdown 항목 추가 및 바인딩
    if (ResolutionDropdown)
    {
        ResolutionDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnResolutionSelectionChanged);

        ResolutionDropdown->AddOption(TEXT("800x600"));
        ResolutionDropdown->AddOption(TEXT("1024x768"));
        ResolutionDropdown->AddOption(TEXT("1280x720"));
        ResolutionDropdown->AddOption(TEXT("1920x1080"));

        ResolutionDropdown->SetSelectedOption(TEXT("800x600"));  // 기본 선택
    }

    // ShadowQualityDropdown 항목 추가 및 바인딩
    if (ShadowQualityDropdown)
    {
        ShadowQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnShadowQualitySelectionChanged);

        ShadowQualityDropdown->AddOption(TEXT("Low"));
        ShadowQualityDropdown->AddOption(TEXT("Medium"));
        ShadowQualityDropdown->AddOption(TEXT("High"));
        ShadowQualityDropdown->AddOption(TEXT("Epic"));
        ShadowQualityDropdown->AddOption(TEXT("Cinematic"));

        ShadowQualityDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // TextureQualityDropdown 항목 추가 및 바인딩
    if (TextureQualityDropdown)
    {
        TextureQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnTextureQualitySelectionChanged);

        TextureQualityDropdown->AddOption(TEXT("Low"));
        TextureQualityDropdown->AddOption(TEXT("Medium"));
        TextureQualityDropdown->AddOption(TEXT("High"));
        TextureQualityDropdown->AddOption(TEXT("Epic"));
        TextureQualityDropdown->AddOption(TEXT("Cinematic"));

        TextureQualityDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // ReflectionQualityDropdown 항목 추가 및 바인딩
    if (ReflectionQualityDropdown)
    {
        ReflectionQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnReflectionQualitySelectionChanged);

        ReflectionQualityDropdown->AddOption(TEXT("Low"));
        ReflectionQualityDropdown->AddOption(TEXT("Medium"));
        ReflectionQualityDropdown->AddOption(TEXT("High"));
        ReflectionQualityDropdown->AddOption(TEXT("Epic"));
        ReflectionQualityDropdown->AddOption(TEXT("Cinematic"));

        ReflectionQualityDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // ViewDistanceDropdown 항목 추가 및 바인딩
    if (ViewDistanceDropdown)
    {
        ViewDistanceDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnViewDistanceSelectionChanged);

        ViewDistanceDropdown->AddOption(TEXT("Low"));
        ViewDistanceDropdown->AddOption(TEXT("Medium"));
        ViewDistanceDropdown->AddOption(TEXT("High"));
        ViewDistanceDropdown->AddOption(TEXT("Epic"));
        ViewDistanceDropdown->AddOption(TEXT("Cinematic"));

        ViewDistanceDropdown->SetSelectedOption(TEXT("Low"));  // 기본 선택
    }

    // GlobalIlluminationDropdown 항목 추가 및 바인딩
    if (GlobalIlluminationDropdown)
    {
        GlobalIlluminationDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnGlobalIlluminationSelectionChanged);

        GlobalIlluminationDropdown->AddOption(TEXT("Low"));
        GlobalIlluminationDropdown->AddOption(TEXT("Medium"));
        GlobalIlluminationDropdown->AddOption(TEXT("High"));
        GlobalIlluminationDropdown->AddOption(TEXT("Epic"));
        GlobalIlluminationDropdown->AddOption(TEXT("Cinematic"));

        GlobalIlluminationDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // AntiAliasingDropdown 항목 추가 및 바인딩
    if (AntiAliasingDropdown)
    {
        AntiAliasingDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnAntiAliasingSelectionChanged);

        AntiAliasingDropdown->AddOption(TEXT("Low"));
        AntiAliasingDropdown->AddOption(TEXT("Medium"));
        AntiAliasingDropdown->AddOption(TEXT("High"));
        AntiAliasingDropdown->AddOption(TEXT("Epic"));
        AntiAliasingDropdown->AddOption(TEXT("Cinematic"));

        AntiAliasingDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // EffectsQualityDropdown 항목 추가 및 바인딩
    if (EffectsQualityDropdown)
    {
        EffectsQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnEffectsQualitySelectionChanged);

        EffectsQualityDropdown->AddOption(TEXT("Low"));
        EffectsQualityDropdown->AddOption(TEXT("Medium"));
        EffectsQualityDropdown->AddOption(TEXT("High"));
        EffectsQualityDropdown->AddOption(TEXT("Epic"));
        EffectsQualityDropdown->AddOption(TEXT("Cinematic"));

        EffectsQualityDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // FoliageQualityDropdown 항목 추가 및 바인딩
    if (FoliageQualityDropdown)
    {
        FoliageQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnFoliageQualitySelectionChanged);

        FoliageQualityDropdown->AddOption(TEXT("Low"));
        FoliageQualityDropdown->AddOption(TEXT("Medium"));
        FoliageQualityDropdown->AddOption(TEXT("High"));
        FoliageQualityDropdown->AddOption(TEXT("Epic"));
        FoliageQualityDropdown->AddOption(TEXT("Cinematic"));

        FoliageQualityDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }

    // ShadingQualityDropdown 항목 추가 및 바인딩
    if (ShadingQualityDropdown)
    {
        ShadingQualityDropdown->OnSelectionChanged.AddDynamic(this, &UGraphicsSettings::OnShadingQualitySelectionChanged);

        ShadingQualityDropdown->AddOption(TEXT("Low"));
        ShadingQualityDropdown->AddOption(TEXT("Medium"));
        ShadingQualityDropdown->AddOption(TEXT("High"));
        ShadingQualityDropdown->AddOption(TEXT("Epic"));
        ShadingQualityDropdown->AddOption(TEXT("Cinematic"));

        ShadingQualityDropdown->SetSelectedOption(TEXT("Epic"));  // 기본 선택
    }
}

void UGraphicsSettings::OnScreenModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
    {
        if (SelectedItem == TEXT("Fullscreen"))
        {
            UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
        }
        else if (SelectedItem == TEXT("Windowed"))
        {
            UserSettings->SetFullscreenMode(EWindowMode::Windowed);
        }
        else if (SelectedItem == TEXT("Windowed Fullscreen"))
        {
            UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
        }

        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}

void UGraphicsSettings::OnResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (ResolutionDropdown)
    {
        FString SelectedResolution = ResolutionDropdown->GetSelectedOption();
        TArray<FString> ResolutionParts;
        SelectedResolution.ParseIntoArray(ResolutionParts, TEXT("x"), true);

        if (ResolutionParts.Num() == 2)
        {
            int32 Width = FCString::Atoi(*ResolutionParts[0]);
            int32 Height = FCString::Atoi(*ResolutionParts[1]);

            UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
            if (UserSettings)
            {
                UserSettings->SetScreenResolution(FIntPoint(Width, Height));
                UserSettings->ApplySettings(false);
                UserSettings->SaveSettings();
            }
        }
    }
}

void UGraphicsSettings::OnShadowQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
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
        else if (SelectedItem == TEXT("Epic"))
        {
            QualityLevel = 3;
        }
        else if (SelectedItem == TEXT("Cinematic"))
        {
            QualityLevel = 4;
        }
        UserSettings->SetShadowQuality(QualityLevel);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}

void UGraphicsSettings::OnTextureQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
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
        else if (SelectedItem == TEXT("Epic"))
        {
            QualityLevel = 3;
        }
        else if (SelectedItem == TEXT("Cinematic"))
        {
            QualityLevel = 4;
        }
        UserSettings->SetTextureQuality(QualityLevel);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}

void UGraphicsSettings::OnReflectionQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
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
        else if (SelectedItem == TEXT("Epic"))
        {
            QualityLevel = 3;
        }
        else if (SelectedItem == TEXT("Cinematic"))
        {
            QualityLevel = 4;
        }
        UserSettings->SetReflectionQuality(QualityLevel);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}

void UGraphicsSettings::OnViewDistanceSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
    {
        // 선택된 항목을 기반으로 품질 수준을 설정
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
        else if (SelectedItem == TEXT("Epic"))
        {
            QualityLevel = 3;
        }
        else if (SelectedItem == TEXT("Cinematic"))
        {
            QualityLevel = 4;
        }

        // 뷰 거리 품질을 설정하고, 설정을 적용 및 저장
        UserSettings->SetViewDistanceQuality(QualityLevel);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}

void UGraphicsSettings::OnAntiAliasingSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
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
        else if (SelectedItem == TEXT("Epic"))
        {
            QualityLevel = 3;
        }
        else if (SelectedItem == TEXT("Cinematic"))
        {
            QualityLevel = 4;
        }
        UserSettings->SetAntiAliasingQuality(QualityLevel);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}

void UGraphicsSettings::OnEffectsQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
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
    else if (SelectedItem == TEXT("Epic"))
    {
        QualityLevel = 3;
    }
    else if (SelectedItem == TEXT("Cinematic"))
    {
        QualityLevel = 4;
    }

    FString Command = FString::Printf(TEXT("r.EffectsQuality %d"), QualityLevel);
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnFoliageQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
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
    else if (SelectedItem == TEXT("Epic"))
    {
        QualityLevel = 3;
    }
    else if (SelectedItem == TEXT("Cinematic"))
    {
        QualityLevel = 4;
    }

    FString Command = FString::Printf(TEXT("r.FoliageQuality %d"), QualityLevel);
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnShadingQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
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
    else if (SelectedItem == TEXT("Epic"))
    {
        QualityLevel = 3;
    }
    else if (SelectedItem == TEXT("Cinematic"))
    {
        QualityLevel = 4;
    }

    FString Command = FString::Printf(TEXT("r.ShadingQuality %d"), QualityLevel);
    UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, nullptr);
}

void UGraphicsSettings::OnGlobalIlluminationSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    if (UserSettings)
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
        else if (SelectedItem == TEXT("Epic"))
        {
            QualityLevel = 3;
        }
        else if (SelectedItem == TEXT("Cinematic"))
        {
            QualityLevel = 4;
        }
        UserSettings->SetGlobalIlluminationQuality(QualityLevel);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
    }
}
