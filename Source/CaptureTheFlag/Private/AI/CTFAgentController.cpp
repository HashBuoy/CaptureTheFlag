// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CTFAgentController.h"

#include "Core/CTFGameMode.h"
#include "Core/CTFGameState.h"
#include "Player/CTFPlayerState.h"
#include "Utils/CTFBlueprintFunctionLibrary.h"

uint8 ACTFAgentController::GetTeamId_Implementation() const
{
	return GetPlayerState<ACTFPlayerState>()->GetTeamId();
}

void ACTFAgentController::SetTeamId(uint8 InTeamId)
{
	GetPlayerState<ACTFPlayerState>()->SetTeamId(InTeamId);
}

void ACTFAgentController::BeginPlay()
{
	UE_LOG(LogTemp,Error,TEXT("ACTFAgentController %s BeginPlay"),*this->GetActorNameOrLabel());
	Super::BeginPlay();

	if (ACTFGameState* GameState = GetWorld()->GetGameState<ACTFGameState>())
	{
		GameState->OnRoundStateChanged.AddDynamic(this,	&ThisClass::OnRoundStateChanged);
	}
}

void ACTFAgentController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp,Error,TEXT("ACTFAgentController %s EndPlay"),*this->GetActorNameOrLabel());
	Super::EndPlay(EndPlayReason);
}

void ACTFAgentController::OnRoundStateChanged(ECTFRoundState RoundState)
{
	switch (RoundState)
	{
	case ECTFRoundState::Captured:
		//Stop brain
		break;

	case ECTFRoundState::Reset:
		//Reset brain if valid
		//Reset Character
		if(ACTFGameMode* GameMode = UCTFBlueprintFunctionLibrary::GetCTFGameMode(this))
		{
			GameMode->ResetCharacter(GetCharacter());
		}
		break;

	case ECTFRoundState::Countdown:
		break;

	case ECTFRoundState::Started:
		//Start brain
		break;
		
	default:;
	}
}

void ACTFAgentController::BeginDestroy()
{
	UE_LOG(LogTemp,Error,TEXT("ACTFAgentController %s BeginDestroy"),*this->GetActorNameOrLabel());
	Super::BeginDestroy();
}

void ACTFAgentController::Destroyed()
{
	UE_LOG(LogTemp,Error,TEXT("ACTFAgentController %s Destroyed"),*this->GetActorNameOrLabel());
	Super::Destroyed();
}
