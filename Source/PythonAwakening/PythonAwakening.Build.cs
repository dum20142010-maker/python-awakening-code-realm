// Copyright 2026 Python Awakening Studios. All Rights Reserved.

using UnrealBuildTool;

public class PythonAwakening : ModuleRules
{
    public PythonAwakening(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        // Core Unreal modules
        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "Slate",
            "SlateCore",
            "GameplayTasks",
            "AIModule",
            "NavigationSystem",
            "Json",
            "JsonUtilities"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Python integration
        PublicDependencyModuleNames.Add("Python");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
