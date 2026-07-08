// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CTFAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxSpeed;

	ATTRIBUTE_ACCESSORS_BASIC(UCTFAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UCTFAttributeSet, MaxHealth);

	ATTRIBUTE_ACCESSORS_BASIC(UCTFAttributeSet, Speed);
	ATTRIBUTE_ACCESSORS_BASIC(UCTFAttributeSet, MaxSpeed);
};
