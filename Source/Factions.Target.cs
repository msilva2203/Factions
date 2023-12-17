// Developed by the Factions community

using UnrealBuildTool;
using System.Collections.Generic;

public class FactionsTarget : TargetRules
{
	public FactionsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Factions" } );
	}
}
