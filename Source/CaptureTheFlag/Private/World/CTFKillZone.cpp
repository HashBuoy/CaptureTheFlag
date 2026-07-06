// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CTFKillZone.h"

#include "Components/BoxComponent.h"
#include "Core/CTFGameMode.h"
#include "GameFramework/Character.h"
#include "Utils/CTFBlueprintFunctionLibrary.h"

// Sets default values
ACTFKillZone::ACTFKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ACTFKillZone::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnBoxBeginOverlap);
}

// Called every frame
void ACTFKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTFKillZone::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if(ACTFGameMode* GameMode = UCTFBlueprintFunctionLibrary::GetCTFGameMode(this))
	{
		GameMode->EnteredKillZone(Character);
	}
}