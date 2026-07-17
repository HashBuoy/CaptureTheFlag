// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CTFEnums.h"
#include "GameFramework/GameState.h"
#include "CTFGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStateChanged, ECTFRoundState, RoundState);

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnRoundStateChanged OnRoundStateChanged;

	void SetRoundState(ECTFRoundState NewRoundState);

	void IncrementRound();

	void IncrementScore(uint8 TeamId);

	ECTFRoundState GetCurrentRoundState() const;

	uint8 GetCurrentRound() const;
	
	void AddTeam(uint8 TeamId);

private:
	ECTFRoundState CurrentRoundState;
	
	uint8 CurrentRound = 0;

	TMap<uint8, uint8> TeamScoreMap;
};
