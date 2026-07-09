// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CTFRune.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"

// Sets default values
ACTFRune::ACTFRune()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);

	Mesh->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnRuneOverlap);
}

// Called when the game starts or when spawned
void ACTFRune::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTFRune::OnRuneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if(!IsValid(Character))
	{
		return;
	}
	
	if (!GameplayEffectClass)
	{
		return;
	}

	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (!AbilitySystemInterface)
	{
		return;
	}

	UAbilitySystemComponent* ASC =	AbilitySystemInterface->GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}
	
	const FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	ASC->ApplyGameplayEffectToSelf(GameplayEffectClass->GetDefaultObject<UGameplayEffect>(), 1.f,EffectContext);
	Destroy();
}
