// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTFVictoryCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class CAPTURETHEFLAG_API ACTFVictoryCamera : public AActor
{
	GENERATED_BODY()
	
public:
	ACTFVictoryCamera();

	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* InTarget);

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(Transient)
	TObjectPtr<AActor> Target;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float OrbitSpeed = 45.f;

	float CurrentYaw = 0.f;
};