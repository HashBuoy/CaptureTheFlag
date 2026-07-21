// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CTFBlueprintFunctionLibrary.generated.h"

class ACTFFlag;
class ACTFGameState;
class ACTFGameMode;
/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintPure, Category="CTF", meta=(WorldContext="WorldContextObject"))
	static ACTFGameMode* GetCTFGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="CTF", meta=(WorldContext="WorldContextObject"))
	static ACTFGameState* GetCTFGameState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="CTF")
    static FLinearColor GetTeamColor(uint8 TeamId);

	UFUNCTION(BlueprintPure, Category="CTF")
	static FText GetTeamName(uint8 TeamId);


	UFUNCTION(BlueprintPure, Category="CTF", meta=(WorldContext="WorldContextObject"))
	static ACTFFlag* GetFlag(const UObject* WorldContextObject);
};
