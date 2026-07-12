// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CTFFlag.h"

// Sets default values
ACTFFlag::ACTFFlag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	FlagPoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagPoleMesh"));
	FlagPoleMesh->SetupAttachment(Root);

	
	FlagPoleMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FlagPoleMesh->SetCollisionObjectType(ECC_WorldDynamic);
	FlagPoleMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FlagPoleMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	FlagPoleMesh->SetGenerateOverlapEvents(true);

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	FlagMesh->SetupAttachment(FlagPoleMesh.Get());

	FlagMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FlagMesh->SetCollisionObjectType(ECC_WorldDynamic);
	FlagMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	FlagMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	FlagMesh->SetGenerateOverlapEvents(true);
	
}

void ACTFFlag::PickFlag(ACTFCharacterBase* InCarrier)
{
	Carrier = InCarrier;
}

void ACTFFlag::DropFlag()
{
	Carrier = nullptr;

	//Trace and drop on the ground vertically
}

// Called when the game starts or when spawned
void ACTFFlag::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTFFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

