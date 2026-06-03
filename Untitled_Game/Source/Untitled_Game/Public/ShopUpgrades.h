#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "ShopUpgrades.generated.h"
/*
UENUM(BlueprintType)
enum class EShopUpgradeType : uint8
{
	MaxHealth UMETA(DisplayName = "Max Health"),
	WeaponDamage UMETA(DisplayName = "Weapon Damage"),
	AttackSpeed UMETA(DisplayName = "Attack Speed"),
	WeaponRange UMETA(DisplayName = "Weapon Range"),
	MoveSpeed UMETA(DisplayName = "Move Speed"),
	UnlockWeapon UMETA(DisplayName = "Unlock Weapon")
};
*/
USTRUCT(BlueprintType)
struct UNTITLED_GAME_API FShopUpgradeRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	FGameplayTag UpgradeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	float Value = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	int32 Cost = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	int32 MaxPurchaseCount = 5 ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	bool bCanAppearInRandomShop = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	FName RequiredUpgradeId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	FGameplayTag RequiredClassTag;
};

USTRUCT(BlueprintType)
struct UNTITLED_GAME_API FShopOffer
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Shop")
	FName UpgradeId;

	UPROPERTY(BlueprintReadOnly, Category = "Shop")
	FShopUpgradeRow UpgradeData;
};