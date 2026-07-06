// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CTFGameMode.h"

#include "Data/CTFGameData.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


void ACTFGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	CachePlayerStart();
	SpawnTeams();
}

void ACTFGameMode::CachePlayerStart()
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),PlayerStartActors);

	for(AActor* PlayerStart : PlayerStartActors)
	{
		PlayerStarts.Add(Cast<APlayerStart>(PlayerStart));
	}
}

void ACTFGameMode::SpawnTeams()
{
	for(int32 i = 0 ; i < GameData->NumOfTeams; i++)
	{
		const APlayerStart* PlayerStart = PlayerStart = GetPlayerStartForTeam(i);
		if(!IsValid(PlayerStart))
		{
			UE_LOG(LogTemp, Error, TEXT("Player Start actor not configured for Team : %i"), i);
			continue;
		}

		if(i == 0)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			//Spawn Player Team Controller
			ACTFPlayerTeamController* PlayerTeamController = GetWorld()->SpawnActor<ACTFPlayerTeamController>(PlayerTeamControllerClass, PlayerStart->GetActorTransform(), SpawnInfo);
			if (!IsValid(PlayerTeamController))
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerTeamController is NULL"));
				continue;
			}
		}
		else
		{
			//Spawn AI Team Controller
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			//Spawn Player Team Controller
			ACTFAITeamController* AITeamController = GetWorld()->SpawnActor<ACTFAITeamController>(AITeamControllerClass, PlayerStart->GetActorTransform(), SpawnInfo);
			if (!IsValid(AITeamController))
			{
				UE_LOG(LogTemp, Warning, TEXT("ACTFAITeamController is NULL"));
				continue;
			}
		}
		
		
	}
}

APlayerStart* ACTFGameMode::GetPlayerStartForTeam(int32 TeamId)
{
	const FName TeamTag(*FString::FromInt(TeamId));

	APlayerStart* const* Found = PlayerStarts.FindByPredicate(
		[&TeamTag](const APlayerStart* PlayerStart)
		{
			return PlayerStart &&
				   PlayerStart->PlayerStartTag == TeamTag;
		});
	
	return Found ? *Found : nullptr;
}
