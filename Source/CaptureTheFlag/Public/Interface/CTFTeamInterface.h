// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CTFTeamInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCTFTeamInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAPTURETHEFLAG_API ICTFTeamInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	uint8 GetTeamId() const;

	virtual void SetTeamId(uint8 InTeamId) = 0;
};
