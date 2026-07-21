// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CTFTeamControllerBase.h"

#include "Core/CTFGameState.h"

uint8 ACTFTeamControllerBase::GetTeamId() const
{
	return TeamId;
}

void ACTFTeamControllerBase::SetTeamId(uint8 InTeamId)
{
	TeamId = InTeamId;
}

void ACTFTeamControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (ACTFGameState* GameState = GetWorld()->GetGameState<ACTFGameState>())
	{
		GameState->OnRoundStateChanged.AddDynamic(this,	&ThisClass::OnRoundStateChanged);
	}
}

void ACTFTeamControllerBase::OnRoundStateChanged(ECTFRoundState RoundState)
{
	switch (RoundState)
	{
	case ECTFRoundState::Captured:
		//Stop brain
		break;

	case ECTFRoundState::Reset:
		//Reset brain if valid
		break;

	case ECTFRoundState::Countdown:
		break;

	case ECTFRoundState::Started:
		//Start brain
		break;
		
	default:;
	}
}