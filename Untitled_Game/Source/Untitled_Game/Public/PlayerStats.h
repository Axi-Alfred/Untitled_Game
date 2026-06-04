#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopUpgrades.h"
#include "PlayerStats.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPointsChanged, int32, NewPoints);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNTITLED_GAME_API UPlayerStats : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerStats();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Points")
	int32 Points = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Combat")
	float DamageMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Combat")
	float AttackSpeedMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Combat")
	float RangeMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Movement")
	float MoveSpeedBonus = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Shop")
	TArray<FShopOffer> CurrentShopOffers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats|Upgrades")
	TMap<FName, int32> PurchaseCounts;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnPointsChanged OnPointsChanged;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Points")
	int32 GetPoints() const { return Points; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Points")
	bool CanAfford(int32 Cost) const;

	UFUNCTION(BlueprintCallable, Category = "Stats|Points")
	bool SpendPoints(int32 Cost);

	UFUNCTION(BlueprintCallable, Category = "Stats|Points")
	void AddPoints(int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats|Upgrades")
	int32 GetPurchaseCount(FName UpgradeId) const;

	UFUNCTION(BlueprintCallable, Category = "Stats|Upgrades")
	void AddPurchase(FName UpgradeId);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Combat")
	float WeaponDamageBonus = 0.f;
};