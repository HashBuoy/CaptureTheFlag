// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTFTeamCapturePoint.generated.h"

class USphereComponent;
UCLASS()
class CAPTURETHEFLAG_API ACTFTeamCapturePoint : public AActor
{
	GENERATED_BODY()

public:
	ACTFTeamCapturePoint();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCaptureZoneBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> CaptureZone;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess))
	uint8 TeamId = 0;
};