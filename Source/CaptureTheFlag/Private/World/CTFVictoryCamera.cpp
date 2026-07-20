// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CTFVictoryCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACTFVictoryCamera::ACTFVictoryCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	TObjectPtr<USceneComponent> Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Root);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void ACTFVictoryCamera::BeginPlay()
{
	Super::BeginPlay();
}

void ACTFVictoryCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(Target))
	{
		return;
	}
	
	CurrentYaw += OrbitSpeed * DeltaTime;
	SpringArm->SetRelativeRotation(FRotator(0.f, CurrentYaw, 0.f));
}

void ACTFVictoryCamera::SetTarget(AActor* InTarget)
{
	Target = InTarget;

	if (IsValid(Target))
	{
		SetActorLocation(Target->GetActorLocation());
	}
}