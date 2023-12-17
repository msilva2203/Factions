// Developed by the Factions community

using UnrealBuildTool;
using System.Collections.Generic;

public class FactionsEditorTarget : TargetRules
{
	public FactionsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Factions" } );
	}
}
