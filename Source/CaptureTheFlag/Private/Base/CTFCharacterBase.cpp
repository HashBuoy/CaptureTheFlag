// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CTFCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CTFAbilitySystemComponent.h"
#include "AbilitySystem/CTFAttributeSet.h"
#include "Component/CTFBillboardWidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Data/CTFCharacterDefaultData.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACTFCharacterBase::ACTFCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//Weapon
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh(),"HandGrip_R");

	//Health Widget
	HealthWidget = CreateDefaultSubobject<UCTFBillboardWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetupAttachment(RootComponent.Get());
	HealthWidget->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	HealthWidget->SetWidgetSpace(EWidgetSpace::World);
	HealthWidget->SetDrawSize(FVector2D(120.f, 30.f));
	HealthWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	AbilitySystemComponent = CreateDefaultSubobject<UCTFAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UCTFAttributeSet>(TEXT("AttributeSet"));

}

uint8 ACTFCharacterBase::GetTeamId_Implementation() const
{
	if (Controller && Controller->Implements<UCTFTeamInterface>())
	{
		return ICTFTeamInterface::Execute_GetTeamId(Controller);
	}
	
	return 255;
}

void ACTFCharacterBase::SetTeamId(uint8 InTeamId)
{
	if (ICTFTeamInterface* TeamInterface = Cast<ICTFTeamInterface>(Controller))
	{
		TeamInterface->SetTeamId(InTeamId);
	}
}

UAbilitySystemComponent* ACTFCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ACTFCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UpdateVisuals();
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	SetupDefaultAbilitiesAndAttributes();

	if(IsPlayerControlled())
	{
		HealthWidget->SetVisibility(false);
	}
}

void ACTFCharacterBase::SetupDefaultAbilitiesAndAttributes()
{
	// Grant abilities
	for (auto Ability : DefaultAbilityData->Abilities)
	{
		if (Ability != nullptr)
		{
			FGameplayAbilitySpec Spec(Ability);
			Spec.SourceObject = this;
			if(const UCTFGameplayAbilityBase* CTFAbility = Cast<UCTFGameplayAbilityBase>(Spec.Ability))
			{
				Spec.GetDynamicSpecSourceTags().AddTag(CTFAbility->InputTag);
			}
			AbilitySystemComponent->GiveAbility(Spec);
		}
	}

	//Apply default attributes
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAbilityData->Attributes, 1.0f, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

// Called when the game starts or when spawned
void ACTFCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCTFAttributeSet::GetSpeedAttribute()).AddUObject(this, &ThisClass::OnSpeedAttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCTFAttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	}
}

void ACTFCharacterBase::UpdateVisuals_Implementation()
{
}

// Called every frame
void ACTFCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTFCharacterBase::OnSpeedAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	GetCharacterMovement()->MaxWalkSpeed = OnAttributeChangeData.NewValue;
	OnAttributeChanged.Broadcast(OnAttributeChangeData.Attribute,OnAttributeChangeData.NewValue);
}

void ACTFCharacterBase::OnHealthAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	OnAttributeChanged.Broadcast(OnAttributeChangeData.Attribute,OnAttributeChangeData.NewValue);
}

