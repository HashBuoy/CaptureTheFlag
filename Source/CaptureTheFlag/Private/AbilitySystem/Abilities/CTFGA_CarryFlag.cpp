// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CTFGA_CarryFlag.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Data/CTFGameplayTags.h"
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
	if(!Flag->PickFlag(Character))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	Flag->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("FlagSocket"));
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->RegisterGameplayTagEvent(CTFGameplayTags::State::Stunned,EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UCTFGA_CarryFlag::OnStunChanged);
}

void UCTFGA_CarryFlag::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UE_LOG(LogTemp,Error,TEXT("CarryFlag EndAbility"));
	if(IsValid(Flag))
	{
		Flag->DropFlag();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}

void UCTFGA_CarryFlag::OnStunChanged(FGameplayTag GameplayTag, int Count)
{
	if(Count > 0)
	{
		EndAbility(	CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
	}
}
