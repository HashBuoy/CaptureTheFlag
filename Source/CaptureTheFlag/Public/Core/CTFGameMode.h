// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CTFGameData.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCTFGameData> GameData;
	
};
