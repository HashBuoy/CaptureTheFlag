// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "NativeGameplayTags.h"

namespace CTFGameplayTags
{
	namespace Input 
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shoot);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(PickUpFlag);
	}

	namespace Ability
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shoot);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(PickUpFlag);
	}

	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stunned);
	}
}