// Copyright Epic Games, Inc. All Rights Reserved.


#include "Player/CaptureTheFlagPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "CaptureTheFlag.h"
#include "Core/CTFGameState.h"
#include "Player/CTFPlayerState.h"
#include "Utils/CTFBlueprintFunctionLibrary.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "World/CTFFlag.h"
#include "World/CTFVictoryCamera.h"

uint8 ACaptureTheFlagPlayerController::GetTeamId_Implementation() const
{
	return GetPlayerState<ACTFPlayerState>()->GetTeamId();
}

void ACaptureTheFlagPlayerController::SetTeamId(uint8 InTeamId)
{
	GetPlayerState<ACTFPlayerState>()->SetTeamId(InTeamId);
}

void ACaptureTheFlagPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogCaptureTheFlag, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}

	
	if (ACTFGameState* GameState = GetWorld()->GetGameState<ACTFGameState>())
	{
		GameState->OnRoundStateChanged.AddDynamic(this,	&ThisClass::OnRoundStateChanged);
	}
}

void ACaptureTheFlagPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

void ACaptureTheFlagPlayerController::OnRoundStateChanged(ECTFRoundState RoundState)
{
	switch (RoundState)
	{
	case ECTFRoundState::Captured:
		{
			SetIgnoreMoveInput(true);
			SetIgnoreLookInput(true);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ACTFFlag* Flag = UCTFBlueprintFunctionLibrary::GetFlag(this);
			VictoryCamera = GetWorld()->SpawnActor<ACTFVictoryCamera>(VictoryCameraClass,Flag->GetActorLocation(),FRotator::ZeroRotator, SpawnParams);
			if (!IsValid(VictoryCamera))
			{
				return;
			}
		
			VictoryCamera->SetTarget(Flag);
			SetViewTargetWithBlend(	VictoryCamera,1.0f,VTBlend_Cubic);
		
			break;
		}

	case ECTFRoundState::Reset:
		SetIgnoreMoveInput(true);
		SetIgnoreLookInput(true);
		//Delete Victory Cam
		break;

	case ECTFRoundState::Countdown:
		//Disable Input
		SetIgnoreMoveInput(true);
		SetIgnoreLookInput(true);
		break;

	case ECTFRoundState::Started:
		//Enable Input
		ResetIgnoreInputFlags();
		break;
		
		default:;
	}
}
