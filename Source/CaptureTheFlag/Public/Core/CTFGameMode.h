// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

class ACTFAgentCharacter;
class ACTFPlayerTeamController;
class ACTFAITeamController;
class APlayerStart;
class UCTFGameData;
/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
private:
	void CachePlayerStart();
	
	void SpawnTeamControllers();
	
	void SpawnTeamAgents(int32 TeamId, int32 Count);

	FTransform GetPlayerStartTransformForTeam(int32 TeamId);
	
	APlayerStart* GetPlayerStartForTeam(int32 TeamId);
	
protected:
	virtual void OnPostLogin(AController* NewPlayer) override;
	
	virtual void HandleMatchHasStarted() override;

private:
	UPROPERTY(EditDefaultsOnly, Category=Data)
	TObjectPtr<UCTFGameData> GameData;

	UPROPERTY(EditDefaultsOnly, Category=SpawnClassRefs)
	TSubclassOf<ACTFAITeamController> AITeamControllerClass;

	UPROPERTY(EditDefaultsOnly, Category=SpawnClassRefs)
	TSubclassOf<ACTFPlayerTeamController> PlayerTeamControllerClass;

	UPROPERTY(EditDefaultsOnly, Category=SpawnClassRefs)
	TSubclassOf<ACTFAgentCharacter> AgentCharacterClass;
	
	UPROPERTY(Transient)
	TArray<APlayerStart*> PlayerStarts;
};