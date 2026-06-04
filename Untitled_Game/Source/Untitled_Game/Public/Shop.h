#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopUpgrades.h"
#include "GameplayTagContainer.h"
#include "Shop.generated.h"

class UPlayerStats;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopOffersChanged);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNTITLED_GAME_API UShop : public UActorComponent
{
	GENERATED_BODY()

public:
	UShop();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	UDataTable* UpgradeTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	int32 NumberOfRandomOffers = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	int32 RerollCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Always Available")
	int32 HealthPotionCost = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Always Available")
	float HealthPotionHealAmount = 25.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Always Available")
	int32 DefenseHealCost = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Always Available")
	float DefenseHealAmount = 50.f;

	UPROPERTY(BlueprintAssignable, Category = "Shop")
	FOnShopOffersChanged OnShopOffersChanged;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void GenerateOffers(AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool BuyOffer(int32 OfferIndex, AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool RerollOffers(AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Shop|Always Available")
	bool BuyHealthPotion(AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Shop|Always Available")
	bool BuyDefenseHeal(AActor* Player);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Shop")
	TArray<FShopOffer> GetCurrentOffers(AActor* Player) const;

private:
	bool IsUpgradeAvailable(FName UpgradeId, const FShopUpgradeRow& Row, UPlayerStats* Stats) const;

	void ApplyUpgrade(FName UpgradeId, const FShopUpgradeRow& Row, AActor* Player);
};