// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class KingOfTheShip_MainTarget : TargetRules
{
	public KingOfTheShip_MainTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "KingOfTheShip_Main" } );
	}
}
