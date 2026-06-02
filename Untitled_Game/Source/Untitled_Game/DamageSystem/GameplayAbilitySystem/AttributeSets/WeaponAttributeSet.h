// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WeaponAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_GAME_API UWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UWeaponAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Range)
	FGameplayAttributeData Range;
	ATTRIBUTE_ACCESSORS_BASIC(UWeaponAttributeSet, Range);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS_BASIC(UWeaponAttributeSet, Damage);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Healing)
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS_BASIC(UWeaponAttributeSet, Healing);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS_BASIC(UWeaponAttributeSet, AttackSpeed);
	
public:
	UFUNCTION()
	void OnRep_Range(const FGameplayAttributeData& oldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Range, oldValue);
	}
	
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& oldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Damage, oldValue);
	}
	
	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& oldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, Healing, oldValue);
	}
	
	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& oldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UWeaponAttributeSet, AttackSpeed, oldValue);
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& ExecData) override;
};
