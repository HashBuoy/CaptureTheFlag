// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/CTFCharacterBase.h"
#include "GameFramework/Actor.h"
#include "CTFFlag.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTFFlag();

	void PickFlag(ACTFCharacterBase* InCarrier);

	void DropFlag();

	ACTFCharacterBase* GetCurrentCarrier() const {return Carrier;};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagPoleMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagMesh;

private:
	UPROPERTY(Transient)
	ACTFCharacterBase* Carrier;
};
