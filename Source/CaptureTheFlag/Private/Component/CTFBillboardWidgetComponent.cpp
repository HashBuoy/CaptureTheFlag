// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CTFBillboardWidgetComponent.h"

#include "Kismet/GameplayStatics.h"

UCTFBillboardWidgetComponent::UCTFBillboardWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTFBillboardWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const APlayerCameraManager* CameraManager =	UGameplayStatics::GetPlayerCameraManager(this, 0);

	if (!CameraManager)
	{
		return;
	}

	const FVector CameraLocation = CameraManager->GetCameraLocation();
	const FVector WidgetLocation = GetComponentLocation();
	const FRotator LookAtRotation =	(CameraLocation - WidgetLocation).Rotation();
	SetWorldRotation(LookAtRotation);
}