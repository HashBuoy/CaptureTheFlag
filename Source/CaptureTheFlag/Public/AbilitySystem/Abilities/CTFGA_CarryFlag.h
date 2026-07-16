// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CTFGameplayAbilityBase.h"
#include "CTFGA_CarryFlag.generated.h"

class ACTFFlag;
/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFGA_CarryFlag : public UCTFGameplayAbilityBase
{
	GENERATED_BODY()
public:
	UCTFGA_CarryFlag();

	
	// GameplayAbility interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	UPROPERTY(Transient)
	ACTFFlag* Flag ;

	void OnStunChanged(FGameplayTag GameplayTag, int Count);
};
