// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageSystemTypes.h"
#include "DamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNTITLED_GAME_API IDamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damageable Interface")
	float GetCurrentHealth();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damageable Interface")
	float GetMaxHealth();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damageable Interface")
	bool GetIsDead();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damageable Interface")
	void Heal(float HealAmount, AActor* Healer);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damageable Interface")
	bool TakeDamage(const FDamageInfo& DamageInfo);
};
