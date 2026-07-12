// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CTFGA_Shoot.h"

#include "AbilitySystemComponent.h"
#include "Player/CTFPlayerCharacter.h"

UCTFGA_Shoot::UCTFGA_Shoot()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCTFGA_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ACTFPlayerCharacter* Character = Cast<ACTFPlayerCharacter>(ActorInfo->AvatarActor.Get());

	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	FVector CameraLocation;
	FRotator CameraRotation;

	//Trace from camera mid point into camera forward direction
	Character->Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
	const FVector ViewTraceStart = CameraLocation;
	const FVector ViewTraceEnd = ViewTraceStart + CameraRotation.Vector() * 10000.0f;

	FHitResult ViewHit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);
	GetWorld()->LineTraceSingleByChannel(
		ViewHit,
		ViewTraceStart,
		ViewTraceEnd,
		ECC_Visibility,
		Params);

	FVector HitEnd;
	if(ViewHit.bBlockingHit)
	{
		HitEnd = ViewHit.ImpactPoint;
	}
	else
	{
		HitEnd = ViewHit.TraceEnd;
	}

	//Re-Trace from weapon muzzle location to view hitpoint
	const FVector WeaponTraceStart = Character->GetMuzzleLocation();
	const FVector Direction = (HitEnd - WeaponTraceStart).GetSafeNormal();
	FVector WeaponTraceEnd = WeaponTraceStart + Direction * 11000.0f;

	FHitResult WeaponHit;
	GetWorld()->LineTraceSingleByChannel(
		WeaponHit,
		WeaponTraceStart,
		WeaponTraceEnd,
		ECC_Visibility,
		Params);
	
	if(WeaponHit.bBlockingHit)
	{
		//Apply Damage Effect
		if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(WeaponHit.GetActor()))
		{
			if (UAbilitySystemComponent* ASC =	AbilitySystemInterface->GetAbilitySystemComponent())
			{
				FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
				EffectContext.AddInstigator(Character, Character);
				ASC->ApplyGameplayEffectToSelf(DamageEffectClass->GetDefaultObject<UGameplayEffect>(), 1.f,EffectContext);
			}
		}

		//Draw bullet trajectory
		DrawDebugLine(GetWorld(), WeaponTraceStart, WeaponHit.ImpactPoint, FColor::Green, false, .5f,0,.5f);
	}
	else
	{
		//Draw bullet trajectory
		DrawDebugLine(GetWorld(), WeaponTraceStart, WeaponTraceEnd, FColor::Red, false, .5f,0,.5f);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

