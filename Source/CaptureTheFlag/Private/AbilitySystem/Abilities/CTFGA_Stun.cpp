// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CTFGA_Stun.h"

UCTFGA_Stun::UCTFGA_Stun()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCTFGA_Stun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		//EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	//HitScan fire , apply damage
	UE_LOG(LogTemp,Error,TEXT("Stun ability"));
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
