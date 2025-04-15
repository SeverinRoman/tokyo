// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Tokyo : ModuleRules
{
	public Tokyo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PublicDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime", "UMG", "AIModule", "Niagara", "PhysicsCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "VRM4U", "TweenMaker" });
		
		PublicIncludePaths.AddRange(new string[] {
			"Tokyo",
			"Tokyo/Characters",
			"Tokyo/Components",
			"Tokyo/Enums",
			"Tokyo/GameMods",
			"Tokyo/Interfaces",
			"Tokyo/Managers",
			"Tokyo/NPC",
			"Tokyo/PlayerControllers",
			"Tokyo/Structs",
			"Tokyo/UI",
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
