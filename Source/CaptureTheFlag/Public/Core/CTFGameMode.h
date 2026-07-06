// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/CTFAITeamController.h"
#include "AI/CTFPlayerTeamController.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

class APlayerStart;
class UCTFGameData;
/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	void CachePlayerStart();
	
	void SpawnTeams();

	APlayerStart* GetPlayerStartForTeam(int32 TeamId);
	
protected:
	
	virtual void HandleMatchHasStarted() override;

private:
	UPROPERTY(EditDefaultsOnly, Category=Data)
	TObjectPtr<UCTFGameData> GameData;

	UPROPERTY(EditDefaultsOnly, Category=SpawnClassRefs)
	TSubclassOf<ACTFAITeamController> AITeamControllerClass;

	UPROPERTY(EditDefaultsOnly, Category=SpawnClassRefs)
	TSubclassOf<ACTFPlayerTeamController> PlayerTeamControllerClass;
	
	UPROPERTY(Transient)
	TArray<APlayerStart*> PlayerStarts;
};
