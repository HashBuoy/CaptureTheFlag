// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CTFTeamCapturePoint.h"

#include "Components/SphereComponent.h"
#include "Core/CTFGameMode.h"
#include "World/CTFFlag.h"


ACTFTeamCapturePoint::ACTFTeamCapturePoint()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	CaptureZone = CreateDefaultSubobject<USphereComponent>("CaptureZone");
	CaptureZone->SetupAttachment(Root);

	CaptureZone->SetSphereRadius(450.f);
	CaptureZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CaptureZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	CaptureZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ACTFTeamCapturePoint::BeginPlay()
{
	Super::BeginPlay();
	CaptureZone->OnComponentBeginOverlap.AddDynamic(this, &ACTFTeamCapturePoint::OnCaptureZoneBeginOverlap);
}

void ACTFTeamCapturePoint::OnCaptureZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	ACTFFlag* Flag = Cast<ACTFFlag>(OtherActor);
	if (!IsValid(Flag))
	{
		return;
	}

	ACTFGameMode* GameMode = GetWorld()->GetAuthGameMode<ACTFGameMode>();
	if (!IsValid(GameMode))
	{
		return;
	}

	GameMode->FlagCaptured(TeamId);
}