// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EI : ModuleRules
{
	public EI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput",
            "UMG",
            "GameplayTasks",
            "NavigationSystem",
            "AIModule",
            "Niagara",
            "LevelSequence",
            "Networking",
            "Sockets"
        });

        if (Target.bBuildEditor)
        {
            PublicDependencyModuleNames.Add("UnrealEd");
        }

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.Add("EI");

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }


}
