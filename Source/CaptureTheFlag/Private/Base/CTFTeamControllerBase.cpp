// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CTFTeamControllerBase.h"

uint8 ACTFTeamControllerBase::GetTeamId() const
{
	return TeamId;
}

void ACTFTeamControllerBase::SetTeamId(uint8 InTeamId)
{
	TeamId = InTeamId;
}
