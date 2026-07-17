// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CTFGameState.h"

void ACTFGameState::SetRoundState(ECTFRoundState NewRoundState)
{
	CurrentRoundState = NewRoundState;
	OnRoundStateChanged.Broadcast(CurrentRoundState);
}

void ACTFGameState::IncrementRound()
{
	CurrentRound++;
}

void ACTFGameState::IncrementScore(uint8 TeamId)
{
	if(TeamScoreMap.Contains(TeamId))
	{
		return;
	}

	TeamScoreMap[TeamId]++;
}

ECTFRoundState ACTFGameState::GetCurrentRoundState() const
{
	return CurrentRoundState;
}

uint8 ACTFGameState::GetCurrentRound() const
{
	return CurrentRound;
}

void ACTFGameState::AddTeam(uint8 TeamId)
{
	if(TeamScoreMap.Contains(TeamId))
	{
		return;
	}

	TeamScoreMap.Add(TeamId,0);
}
