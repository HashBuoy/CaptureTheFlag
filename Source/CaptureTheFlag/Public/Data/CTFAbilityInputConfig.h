// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CTFAbilityInputConfig.generated.h"


class UInputAction;

USTRUCT(BlueprintType)
struct CAPTURETHEFLAG_API FCTFTaggedInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> InputAction = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTag InputTag;
};

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFAbilityInputConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/** Ability related inputs */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCTFTaggedInputAction> AbilityInputActions;
};
