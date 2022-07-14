// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SteamV425 : ModuleRules
{
	public SteamV425(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemSteam", "OnlineSubsystemUtils" });

	}
}
