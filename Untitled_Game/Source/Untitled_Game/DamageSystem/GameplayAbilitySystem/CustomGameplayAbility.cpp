// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameplayAbility.h"

UCustomGameplayAbility::UCustomGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.Active")));
}
