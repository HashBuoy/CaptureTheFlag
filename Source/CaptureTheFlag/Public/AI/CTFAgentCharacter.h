// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CTFTeamInterface.h"
#include "CTFAgentCharacter.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFAgentCharacter : public ACharacter, public ICTFTeamInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTFAgentCharacter();

	virtual void PossessedBy(AController* NewController) override;
	
	//~ Team Interface
	virtual uint8 GetTeamId_Implementation() const override;

	virtual void SetTeamId(uint8 InTeamId) override;
	//~~~~~~
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void UpdateVisuals();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
