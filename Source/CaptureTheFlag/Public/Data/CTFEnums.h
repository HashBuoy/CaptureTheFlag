// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTFEnums.generated.h"

UENUM(BlueprintType)
enum class ECTFRoundState : uint8
{
	None,
	Reset,
	Start,
	Completed,
	Max
};
