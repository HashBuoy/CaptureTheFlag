// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CTFGameMode.h"

#include "AI/CTFAgentCharacter.h"
#include "AI/CTFAgentController.h"
#include "AI/CTFAITeamController.h"
#include "AI/CTFPlayerTeamController.h"
#include "Data/CTFGameData.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CaptureTheFlagCharacter.h"
#include "Player/CaptureTheFlagPlayerController.h"


void ACTFGameMode::OnPostLogin(AController* NewPlayer)
{
	ACaptureTheFlagPlayerController* PC = Cast<ACaptureTheFlagPlayerController>(NewPlayer);
	if (PC)
	{
		PC->SetTeamId(0);
	}
	
}

void ACTFGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	
	SpawnTeamControllers();
}

AActor* ACTFGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	CachePlayerStart();
	return GetPlayerStartForTeam(0);
}



void ACTFGameMode::SpawnTeamControllers()
{
	CachePlayerStart();
	
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
			PlayerTeamController->SetTeamId(0);
			
			SpawnTeamAgentControllers(0, GameData->NumOfAgentsPerTeam-1);
		}
		else
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			//Spawn AI Team Controller
			ACTFAITeamController* AITeamController = GetWorld()->SpawnActor<ACTFAITeamController>(AITeamControllerClass, PlayerStart->GetActorTransform(), SpawnInfo);
			if (!IsValid(AITeamController))
			{
				UE_LOG(LogTemp, Warning, TEXT("ACTFAITeamController is NULL"));
				continue;
			}
			AITeamController->SetTeamId(i);
			
			SpawnTeamAgentControllers(i, GameData->NumOfAgentsPerTeam);
		}
	}
}

void ACTFGameMode::SpawnTeamAgentControllers(uint8 TeamId, uint8 Count)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for(int32 i = 0 ; i < Count; i++)
	{
		ACTFAgentController* AgentController = GetWorld()->SpawnActor<ACTFAgentController>(AgentControllerClass, GetPlayerStartTransformForTeam(TeamId), SpawnInfo);
		AgentController->SetTeamId(TeamId);
		AgentController->Possess(SpawnTeamAgent(TeamId));
	}
}

ACTFAgentCharacter* ACTFGameMode::SpawnTeamAgent(uint8 TeamId)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ACTFAgentCharacter* AgentCharacter = GetWorld()->SpawnActor<ACTFAgentCharacter>(AgentCharacterClass, GetPlayerStartTransformForTeam(TeamId), SpawnInfo);
	return AgentCharacter; 
}

void ACTFGameMode::CachePlayerStart()
{
	if (!PlayerStarts.IsEmpty())
	{
		return;
	}
	
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),PlayerStartActors);

	for(AActor* PlayerStart : PlayerStartActors)
	{
		PlayerStarts.Add(Cast<APlayerStart>(PlayerStart));
	}
}

FTransform ACTFGameMode::GetPlayerStartTransformForTeam(uint8 TeamId)
{
	const APlayerStart* PlayerStart = PlayerStart = GetPlayerStartForTeam(TeamId);
	const FVector2D Offset2D = FMath::RandPointInCircle(250.f);
	const FVector Location = PlayerStart->GetActorLocation() + FVector(Offset2D,0);
	return FTransform( PlayerStart->GetActorRotation() , Location,  FVector::OneVector);
}

APlayerStart* ACTFGameMode::GetPlayerStartForTeam(uint8 TeamId)
{
	const FName TeamTag(*FString::FromInt(TeamId));

	APlayerStart* const* Found = PlayerStarts.FindByPredicate(
		[&TeamTag](const APlayerStart* PlayerStart)
		{
			return PlayerStart && PlayerStart->PlayerStartTag == TeamTag;
		});
	
	return Found ? *Found : nullptr;
}

void ACTFGameMode::ResetCharacter(ACharacter* Character)
{
	if(!IsValid(Character))
	{
		return;;
	}

	if(Character->GetController()->IsA(ACaptureTheFlagPlayerController::StaticClass()))
	{
		AController* Controller = Character->GetController();
		Character->Destroy();
		RestartPlayer(Controller);
	}
	else if(Character->GetController()->IsA(ACTFAgentController::StaticClass()))
	{
		ACTFAgentController* Controller = Character->GetController<ACTFAgentController>();
		Character->Destroy();
		Controller->Possess(SpawnTeamAgent(Controller->GetTeamId()));
	}
}
