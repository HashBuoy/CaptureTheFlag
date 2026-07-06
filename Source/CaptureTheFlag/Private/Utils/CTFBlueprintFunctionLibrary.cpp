// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/CTFBlueprintFunctionLibrary.h"

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
