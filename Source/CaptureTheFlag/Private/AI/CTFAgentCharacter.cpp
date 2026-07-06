// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CTFAgentCharacter.h"

// Sets default values
ACTFAgentCharacter::ACTFAgentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTFAgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTFAgentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTFAgentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

