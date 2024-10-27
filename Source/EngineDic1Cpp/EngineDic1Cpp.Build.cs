// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EngineDic1Cpp : ModuleRules
{
	public EngineDic1Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
