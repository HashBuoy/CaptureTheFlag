// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CTFAgentCharacter.h"

#include "GameFramework/Controller.h"

// Sets default values
ACTFAgentCharacter::ACTFAgentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACTFAgentCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UpdateVisuals();
}

uint8 ACTFAgentCharacter::GetTeamId_Implementation() const
{
	if (const ICTFTeamInterface* TeamInterface = Cast<ICTFTeamInterface>(Controller))
	{
		return TeamInterface->GetTeamId();
	}
	
	return 255;
}

void ACTFAgentCharacter::SetTeamId(uint8 InTeamId)
{
	if (ICTFTeamInterface* TeamInterface = Cast<ICTFTeamInterface>(Controller))
	{
		TeamInterface->SetTeamId(InTeamId);
	}
}

// Called when the game starts or when spawned
void ACTFAgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTFAgentCharacter::UpdateVisuals_Implementation()
{
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

