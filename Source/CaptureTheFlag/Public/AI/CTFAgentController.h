// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CTFAgentController.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFAgentController : public AAIController
{
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void BeginDestroy() override;
	virtual void Destroyed() override;
private:
	GENERATED_BODY()
};
