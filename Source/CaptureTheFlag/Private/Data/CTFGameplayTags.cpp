// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CTFGameplayTags.h"


namespace CTFGameplayTags
{
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shoot, "Input.Shoot", "Shoot input");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "Input.Stun", "Stun input");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(CarryFlag, "Input.CarryFlag", "CarryFlag input");
    }

    namespace Ability
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shoot, "Ability.Shoot", "Shoot ability");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "Ability.Stun", "Stun ability");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(CarryFlag, "Ability.CarryFlag", "CarryFlag ability");
    }

    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stunned, "State.Stunned", "Stunned state");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(CarryingFlag, "State.CarryingFlag", "Carrying Flag state");
    }

    namespace Cooldown
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stunned, "Cooldown.Shoot", "Shoot Cooldown");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(CarryingFlag, "Cooldown.Stun", "Stun Cooldown");
    }
}