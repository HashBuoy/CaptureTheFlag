// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CTFAgentController.h"

void ACTFAgentController::BeginPlay()
{
	UE_LOG(LogTemp,Error,TEXT("ACTFAgentController %s BeginPlay"),*this->GetActorNameOrLabel());
	Super::BeginPlay();
}

void ACTFAgentController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp,Error,TEXT("ACTFAgentController %s EndPlay"),*this->GetActorNameOrLabel());
	Super::EndPlay(EndPlayReason);
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
