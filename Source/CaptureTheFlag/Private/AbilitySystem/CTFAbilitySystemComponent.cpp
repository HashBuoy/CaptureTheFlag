// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CTFAbilitySystemComponent.h"

bool UCTFAbilitySystemComponent::AbilityInputPressed(FGameplayTag InputTag)
{
	for(auto& AbilitySpec: GetActivatableAbilities())
	{
		if(AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{
				return TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
	
	return false;
}

void UCTFAbilitySystemComponent::AbilityInputReleased(FGameplayTag InputTag)
{
	for(auto& AbilitySpec: GetActivatableAbilities())
	{
		if(AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}
