// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interface/CTFTeamInterface.h"
#include "CTFTeamControllerBase.generated.h"

enum class ECTFRoundState : uint8;
/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFTeamControllerBase : public AAIController
{

private:
	GENERATED_BODY()

public:
	uint8 GetTeamId() const;

	void SetTeamId(uint8 InTeamId);

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRoundStateChanged(ECTFRoundState RoundState);
	
private:
	uint8 TeamId;
};
