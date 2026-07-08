// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CTFGameplayTags.h"


namespace RQGameplayTags
{
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shoot, "Input.Shoot", "Shoot input");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "Input.Stun", "Stun input");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(PickUpFlag, "Input.PickUpFlag", "PickUpFlag input");
    }

    namespace Ability
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Shoot, "Ability.Shoot", "Shoot ability");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "Ability.Stun", "Stun ability");
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(PickUpFlag, "Ability.PickUpFlag", "PickUpFlag ability");
    }

    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stunned, "State.Stunned", "Stunned state");
    }
}