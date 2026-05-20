// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "ShopUpgradeInterface.generated.h"

UINTERFACE(BlueprintType)
class UNTITLED_GAME_API UShopUpgradeInterface : public UInterface
{
	GENERATED_BODY()
};

class UNTITLED_GAME_API IShopUpgradeInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Shop|Upgrade")
	void ApplyShopUpgrade(FName UpgradeId, FGameplayTag UpgradeTag, float Value);
};