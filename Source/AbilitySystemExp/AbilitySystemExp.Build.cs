using UnrealBuildTool;

public class AbilitySystemExp : ModuleRules
{
	public AbilitySystemExp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
