// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CTFAttributeSet.h"

#include "GameplayEffectExtension.h"

void UCTFAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxSpeed());
	}
}

void UCTFAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		SetSpeed(FMath::Clamp(GetSpeed(), 0.f, GetMaxSpeed()));
	}
}
