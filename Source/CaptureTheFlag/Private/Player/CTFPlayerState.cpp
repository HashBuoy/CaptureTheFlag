// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CTFPlayerState.h"

uint8 ACTFPlayerState::GetTeamId()
{
	return TeamId;
}

void ACTFPlayerState::SetTeamId(uint8 InTeamId)
{
	TeamId = InTeamId;
}
