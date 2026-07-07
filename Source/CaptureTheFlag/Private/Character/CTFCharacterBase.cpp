// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CTFCharacterBase.h"

// Sets default values
ACTFCharacterBase::ACTFCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTFCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTFCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTFCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

