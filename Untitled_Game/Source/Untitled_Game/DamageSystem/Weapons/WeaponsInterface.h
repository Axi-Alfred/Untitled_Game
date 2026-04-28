// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInfo.h"
#include "WeaponsData.h"
#include "UObject/Interface.h"
#include "WeaponsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWeaponsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNTITLED_GAME_API IWeaponsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapons Interface")
	void EquipWeapon(FWeaponsData WeaponsData, APlayerCharacter* Player);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapons Interface")
	void UnequipWeapon(EWeaponNames WeaponNames);
};
