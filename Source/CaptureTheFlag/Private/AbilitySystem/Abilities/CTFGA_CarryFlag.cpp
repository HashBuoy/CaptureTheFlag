// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CTFGA_CarryFlag.h"

#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Utils/CTFBlueprintFunctionLibrary.h"

UCTFGA_CarryFlag::UCTFGA_CarryFlag()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCTFGA_CarryFlag::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	Flag = UCTFBlueprintFunctionLibrary::GetFlag(GetWorld());
	if(!IsValid(Flag))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ACTFCharacterBase* Character = Cast<ACTFCharacterBase>(CurrentActorInfo->AvatarActor.Get());
	if(Flag->PickFlag(Character))
	{
		Flag->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("FlagSocket"));
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}

void UCTFGA_CarryFlag::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UE_LOG(LogTemp,Error,TEXT("CarryFlag EndAbility"));
	if(IsValid(Flag))
	{
		Flag->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Flag->DropFlag();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}
