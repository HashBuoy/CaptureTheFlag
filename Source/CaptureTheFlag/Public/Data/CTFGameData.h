// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CTFGameData.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NumOfTeams = 2;
	
	UPROPERTY(EditDefaultsOnly)
	int32 NumOfAgentsPerTeam = 2;

	UPROPERTY(EditDefaultsOnly)
	int32 NumOfRounds = 3;

	
};
