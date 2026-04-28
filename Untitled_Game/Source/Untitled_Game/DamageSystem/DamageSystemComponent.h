// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageSystemTypes.h"
#include "Components/ActorComponent.h"
#include "DamageSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, const FDamageInfo&, DamageInfo);
// BLOCKING //
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageAvoided, const FDamageInfo&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealReceived, float, HealAmount, AActor*, Healer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNTITLED_GAME_API UDamageSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageSystemComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.0f;
	
private:
	UPROPERTY()
	float CurrentHealth = MaxHealth;
	
	UPROPERTY()
	bool IsDead = false;
	
	UPROPERTY()
	bool IsAttacking = false;
	
	//bool IsBlocking?

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool HandleIncomingDamage(const FDamageInfo& DamageInfo);
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void HandleIncomingHeal(float HealAmount, AActor* Healer);
	
	// GETTER FUNCTIONS //
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetCurrentHealth() { return CurrentHealth; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool GetIsDead() const { return IsDead; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Damage")
	bool GetIsAttacking() const { return IsAttacking; };
	
	// SETTER FUNCTIONS //
	// Set IsBlocking...
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetStartingHealth(float StartingHealth);
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SetIsAttacking(bool ActorIsAttacking);
	
	
	// DELEGATES //
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDamageTaken OnDamageTaken;
	
	// BLOCKING //
	//UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	//FOnDamageAvoided OnDamageAvoided;
	
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDeath OnDeath;
	
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnHealReceived OnHealReceived;
};
