// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/CTFBlueprintFunctionLibrary.h"

#include "EngineUtils.h"
#include "Core/CTFGameMode.h"
#include "Kismet/GameplayStatics.h"

ACTFGameMode* UCTFBlueprintFunctionLibrary::GetCTFGameMode(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
	{
		return nullptr;
	}

	return Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
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
