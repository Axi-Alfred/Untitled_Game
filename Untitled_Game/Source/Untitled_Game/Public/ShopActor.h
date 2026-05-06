#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopActor.generated.h"

class UBoxComponent;
class UShop;

UCLASS()
class UNTITLED_GAME_API AShopActor : public AActor
{
	GENERATED_BODY()

public:
	AShopActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	UBoxComponent* InteractionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	UShop* ShopComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Shop")
	AActor* PlayerInRange = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Shop")
	bool IsPlayerInRange(AActor* Player) const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void PrepareShopForPlayer(AActor* Player);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};