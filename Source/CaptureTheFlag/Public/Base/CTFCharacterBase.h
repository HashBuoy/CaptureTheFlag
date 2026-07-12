// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Character.h"
#include "Interface/CTFTeamInterface.h"
#include "CTFCharacterBase.generated.h"

class UCTFBillboardWidgetComponent;
class UWidgetComponent;
class UAttributeSet;
class UCTFCharacterDefaultData;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged,FGameplayAttribute, Attribute,float, NewValue);

UCLASS()
class CAPTURETHEFLAG_API ACTFCharacterBase : public ACharacter, public ICTFTeamInterface , public IAbilitySystemInterface
{
	GENERATED_BODY()

	
	
public:
	// Sets default values for this character's properties
	ACTFCharacterBase();

	//~ Team Interface
	virtual uint8 GetTeamId_Implementation() const override;

	virtual void SetTeamId(uint8 InTeamId) override;
	//~~~~~~

	//~ Team Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~~~~~~
	
	virtual void PossessedBy(AController* NewController) override;
	void SetupDefaultAbilitiesAndAttributes();
	
	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnAttributeChanged OnAttributeChanged;
	
	FVector GetMuzzleLocation() const;
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void UpdateVisuals();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCTFBillboardWidgetComponent> HealthWidget;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	UCTFCharacterDefaultData* DefaultAbilityData;

	void OnSpeedAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;
	void OnHealthAttributeChanged(const FOnAttributeChangeData& OnAttributeChangeData);
};
