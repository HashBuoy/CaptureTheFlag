// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CTFGameplayAbilityBase.h"
#include "Engine/DataAsset.h"
#include "CTFCharacterDefaultData.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFCharacterDefaultData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="Ability")
	TArray<TSubclassOf<UCTFGameplayAbilityBase>> Abilities;

	UPROPERTY(EditDefaultsOnly,Category="Ability")
    TSubclassOf<UGameplayEffect> Attributes;
};
