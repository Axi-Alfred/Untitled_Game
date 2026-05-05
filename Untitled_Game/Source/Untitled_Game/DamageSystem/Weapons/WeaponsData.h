#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponInfo.h"
#include "WeaponsData.generated.h"

USTRUCT(BlueprintType)
struct UNTITLED_GAME_API FWeaponsData: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponNames WeaponName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponTypes WeaponType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Range;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWeaponBase> WeaponClassRef;
};