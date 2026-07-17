// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CTFFlag.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

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

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent.Get());
	InteractionSphere->InitSphereRadius(200.0f);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	// Ignore everything
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Overlap only pawns
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//Delegates
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);

	PromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidget"));
	PromptWidget->SetupAttachment(RootComponent);
	PromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
	PromptWidget->SetVisibility(false);
}

bool ACTFFlag::PickFlag(ACTFCharacterBase* InCarrier)
{
	if(!IsValid(InCarrier))
	{
		return false;
	}

	if(IsValid(Carrier))
	{
		return false;
	}
	
	if(const float Distance = FVector::DistSquared2D(this->GetActorLocation(),InCarrier->GetActorLocation()); Distance>FMath::Square(PickUpDistance))
	{
		return  false;
	}
	
	Carrier = InCarrier;
	PromptWidget->SetVisibility(false);
	return true;
}

void ACTFFlag::DropFlag()
{
	Carrier = nullptr;

	//Trace and drop on the ground vertically
	FVector Start = GetActorLocation() + FVector(0.f, 0.f, 200.f);
	FVector End   = Start - FVector(0.f, 0.f, 5000.f);

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_WorldStatic,Params))
	{
		SetActorLocation(Hit.Location);

		// Keep flag upright
		SetActorRotation(FRotator::ZeroRotator);
	}
	else
	{
		//Place back to center of the map
	}
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

#if WITH_EDITOR
void ACTFFlag::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, PickUpDistance))
	{
		InteractionSphere->SetSphereRadius(PickUpDistance);
	}
}
#endif

void ACTFFlag::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if(IsValid(Carrier))
	{
		return;
	}
	
	if (const APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (Pawn->IsPlayerControlled())
		{
			PromptWidget->SetVisibility(true);
		}
	}
}

void ACTFFlag::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (const APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (Pawn->IsPlayerControlled())
		{
			PromptWidget->SetVisibility(false);
		}
	}
}

