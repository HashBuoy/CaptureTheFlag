// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/CTFCharacterBase.h"
#include "Data/CTFEnums.h"
#include "GameFramework/Actor.h"
#include "CTFFlag.generated.h"

class USphereComponent;
UCLASS()
class CAPTURETHEFLAG_API ACTFFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTFFlag();
	
	void Reset();

	bool PickFlag(ACTFCharacterBase* InCarrier);

	void DropFlag();

	float GetPickUpDistance() const {return PickUpDistance;};
	
	ACTFCharacterBase* GetCurrentCarrier() const {return Carrier;};
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRoundStateChanged(ECTFRoundState RoundState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagPoleMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> InteractionSphere;

	UPROPERTY(EditDefaultsOnly)
	float PickUpDistance;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
private:
	UPROPERTY(Transient)
	ACTFCharacterBase* Carrier;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> PromptWidget;

	FTransform InitialTransform;
	
	//Sphere overlap functions
	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
