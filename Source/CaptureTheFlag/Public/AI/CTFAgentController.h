// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interface/CTFTeamInterface.h"
#include "CTFAgentController.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFAgentController : public AAIController, public ICTFTeamInterface
{
	GENERATED_BODY()
public:
	//~ Team Interface
	virtual uint8 GetTeamId_Implementation() const override;

	virtual void SetTeamId(uint8 InTeamId) override;
	//~~~~~~
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void BeginDestroy() override;
	virtual void Destroyed() override;
};
