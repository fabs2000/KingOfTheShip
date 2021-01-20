// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class KingOfTheShip_MainEditorTarget : TargetRules
{
	public KingOfTheShip_MainEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "KingOfTheShip_Main" } );
	}
}
