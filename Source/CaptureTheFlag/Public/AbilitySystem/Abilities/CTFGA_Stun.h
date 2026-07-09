// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CTFGameplayAbilityBase.h"
#include "CTFGA_Stun.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFGA_Stun : public UCTFGameplayAbilityBase
{
	GENERATED_BODY()
	
	
public:
	UCTFGA_Stun();

	// GameplayAbility interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
