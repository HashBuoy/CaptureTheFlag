// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AsyncTasks/CTFWaitAbilityCooldownChange.h"

#include "AbilitySystemComponent.h"

UCTFWaitAbilityCooldownChange* UCTFWaitAbilityCooldownChange::WaitAbilityCooldownChange(UAbilitySystemComponent* InASC,const FGameplayTag& InCooldownTag)
{
	UCTFWaitAbilityCooldownChange* WaitAbilityCooldownChange = NewObject<UCTFWaitAbilityCooldownChange>();
	WaitAbilityCooldownChange->ASC = InASC;
	WaitAbilityCooldownChange->CooldownTag = InCooldownTag;

	if(!IsValid(InASC) || !InCooldownTag.IsValid())
	{
		WaitAbilityCooldownChange->EndTask();
		return nullptr;
	}

	InASC->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(WaitAbilityCooldownChange,&UCTFWaitAbilityCooldownChange::CooldownTagChanged );
	return WaitAbilityCooldownChange;
}

void UCTFWaitAbilityCooldownChange::EndTask()
{
	if(!IsValid(ASC))
	{
		return;
	}
	
	ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	MarkAsGarbage();
}

void UCTFWaitAbilityCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (!ASC)
	{
		return;
	}

	if (NewCount > 0)
	{
		FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FGameplayTagContainer(CooldownTag));
		const TArray<TPair<float,float>> Result = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);

		if (Result.Num() > 0)
		{
			OnCooldownStart.Broadcast(Result[0].Key,Result[0].Value);
		}
	}
	else
	{
		OnCooldownEnd.Broadcast(0,0);
	}
}
