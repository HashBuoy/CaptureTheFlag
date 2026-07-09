// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "NativeGameplayTags.h"

namespace CTFGameplayTags
{
	namespace Input 
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shoot);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CarryFlag);
	}

	namespace Ability
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shoot);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CarryFlag);
	}

	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stunned);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CarryingFlag);
	}

	namespace Cooldown
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shoot);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun);
	}
}

