// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInfo.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


UCLASS()
class UNTITLED_GAME_API AWeaponBase : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AWeaponBase();

	template <class AWeaponBase> AWeaponBase* SpawnWeapon(
		UClass* Class, 
		FVector const* Location, 
		FRotator const* Rotation,
		AActor* Owner = NULL,
		APawn* Instigator = NULL
		)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner              = Owner;
		SpawnInfo.Instigator         = Instigator;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		return (Class != NULL) ? Cast<AWeaponBase>(GetWorld()->SpawnActor(Class, Location, Rotation, SpawnInfo)) : NULL;
	}
private:
	UPROPERTY()
	float CurrentDamageAmount = 0;
	
	UPROPERTY()
	FName CurrentSocketName;
	
	UPROPERTY()
	FWeaponInfo CurrentWeaponInfo {
		CurrentWeaponInfo.WeaponNames = EWeaponNames::None,
		CurrentWeaponInfo.WeaponTypes = EWeaponTypes::None
	};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AWeaponBase* SpawnWeaponActor(AWeaponBase* Weapon, FTransform SpawnTransform);
	//FVector const Location, FRotator const Rotation
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	float GetDamageAmount() const { return CurrentDamageAmount; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FName GetSocketName() const { return CurrentSocketName; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FWeaponInfo GetWeaponInfo() const {return CurrentWeaponInfo; }
	
	// SETTERS
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetDamageAmount(float DamageAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetSocketName(FName SocketName);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetSWeaponInfo(EWeaponNames WeaponNames, EWeaponTypes WeaponTypes);
};

