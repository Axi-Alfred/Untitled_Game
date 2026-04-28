// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInfo.generated.h"

UENUM(BlueprintType)
enum class EWeaponNames : uint8
{
	None UMETA(DisplayName = "None"),
	Gladius UMETA(DisplayName = "Gladius"),
	Scutum UMETA(DisplayName = "Scutum"),
	Labrys UMETA(DisplayName = "Labrys"),
	Arcus UMETA(DisplayName = "Arcus"),
	Trident UMETA(DisplayName = "Trident"),
	CenserStaff UMETA(DisplayName = "Censer Staff"),
	GladiusTitanus UMETA(DisplayName = "Gladius Titanus"),
	ColossusGauntlet UMETA(DisplayName = "Colossus Gauntlet")
};

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Ranged UMETA(DisplayName = "Ranged")
};

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	EWeaponNames WeaponNames = EWeaponNames::None;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	EWeaponTypes WeaponTypes = EWeaponTypes::None;
};