// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SteamV425 : ModuleRules
{
	public SteamV425(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemSteam", "OnlineSubsystemUtils"
			}
		);
	}
}
