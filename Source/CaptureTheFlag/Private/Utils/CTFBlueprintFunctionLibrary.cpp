// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/CTFBlueprintFunctionLibrary.h"

#include "EngineUtils.h"
#include "Core/CTFGameMode.h"
#include "Core/CTFGameState.h"
#include "World/CTFFlag.h"
#include "Kismet/GameplayStatics.h"

ACTFGameMode* UCTFBlueprintFunctionLibrary::GetCTFGameMode(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
	{
		return nullptr;
	}

	return Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

ACTFGameState* UCTFBlueprintFunctionLibrary::GetCTFGameState(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
	{
		return nullptr;
	}

	return Cast<ACTFGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}

FLinearColor UCTFBlueprintFunctionLibrary::GetTeamColor(uint8 TeamId)
{
	switch (TeamId)
	{
	case 0:
		return FLinearColor::Green;

	case 1:
		return FLinearColor::Red;

	default:
		return FLinearColor::White;
	}
}

FText UCTFBlueprintFunctionLibrary::GetTeamName(uint8 TeamId)
{
	switch (TeamId)
	{
	case 0:
		return FText::FromString(TEXT("Green"));

	case 1:
		return FText::FromString(TEXT("Red"));

	default:
		return FText::FromString(TEXT("White"));
	}
}

ACTFFlag* UCTFBlueprintFunctionLibrary::GetFlag(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	for (TActorIterator<ACTFFlag> It(World); It; ++It)
	{
		return *It;
	}

	return nullptr;
}
