// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageSystemTypes.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None UMETA(DisplayName = "None"),
	Physical UMETA(DisplayName = "Physical"),
	Magical UMETA(DisplayName = "Magical"),
	//Other types...
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	None UMETA(DisplayName = "None"),
	HitReaction UMETA(DisplayName = "HitReaction"),
	Knockback UMETA(DisplayName = "Knockback"),
	Stun UMETA(DisplayName = "Stun")
	//Other types...
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float DamageAmount;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	AActor* DamageCauser;
	
	//bool CanBeParried, CanBeBlocked, ShouldForceInterrupt...
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	EDamageType DamageType = EDamageType::None;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	EDamageResponse DamageResponse = EDamageResponse::None;
};
