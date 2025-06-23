// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HW5_please : ModuleRules
{
	public HW5_please(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HW5_please",
			"HW5_please/Variant_Platforming",
			"HW5_please/Variant_Combat",
			"HW5_please/Variant_Combat/AI",
			"HW5_please/Variant_SideScrolling",
			"HW5_please/Variant_SideScrolling/Gameplay",
			"HW5_please/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
