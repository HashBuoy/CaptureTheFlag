// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interface/CTFTeamInterface.h"
#include "CTFTeamControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFTeamControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	uint8 GetTeamId() const;

	void SetTeamId(uint8 InTeamId);

private:
	uint8 TeamId;
};
