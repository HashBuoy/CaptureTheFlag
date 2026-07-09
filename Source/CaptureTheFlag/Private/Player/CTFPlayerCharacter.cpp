// Fill out your copyright notice in the Description page of Project Settings.


#include "Player//CTFPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/CTFAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Data/CTFAbilityInputConfig.h"
#include "GameFramework/SpringArmComponent.h"

ACTFPlayerCharacter::ACTFPlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ACTFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		for(const FCTFTaggedInputAction& AbilityInputAction: AbilityInputConfig->AbilityInputActions)
		{
			EnhancedInputComponent->BindAction(AbilityInputAction.InputAction.Get(), ETriggerEvent::Started, this, &ThisClass::AbilityInputPressed,AbilityInputAction.InputTag);
			EnhancedInputComponent->BindAction(AbilityInputAction.InputAction.Get(), ETriggerEvent::Completed, this, &ThisClass::AbilityInputReleased,AbilityInputAction.InputTag);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACTFPlayerCharacter::AbilityInputPressed(const FInputActionValue& Value, FGameplayTag InputTag)
{
	if(!InputTag.IsValid())
	{
		return;
	}

	if(UCTFAbilitySystemComponent* ASC = Cast<UCTFAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		ASC->AbilityInputPressed(InputTag);
	}

}

void ACTFPlayerCharacter::AbilityInputReleased(const FInputActionValue& Value, FGameplayTag InputTag)
{
	if(!InputTag.IsValid())
	{
		return;
	}

	if(UCTFAbilitySystemComponent* ASC = Cast<UCTFAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		ASC->AbilityInputReleased(InputTag);
	}

}

void ACTFPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ACTFPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ACTFPlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ACTFPlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ACTFPlayerCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ACTFPlayerCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}
