// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UWeaponAttributeSet::UWeaponAttributeSet()
{
	Range = 600.f;
	Damage = 25.f;
	Healing = 25.f;
	AttackSpeed = 2.f;
}

void UWeaponAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Range, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, Healing, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeaponAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
}

void UWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetDamageAttribute())
	{
		if (NewValue > 0.f)
		{
			NewValue *= -1.f;
		}
	}
	
	if (Attribute == GetHealingAttribute())
	{
		if (NewValue < 0.f)
		{
			NewValue *= -1.f;
		}
		
	}
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& ExecData)
{
	Super::PostGameplayEffectExecute(ExecData);
	
	if (ExecData.EvaluatedData.Attribute == GetRangeAttribute())
	{
		SetRange(GetRange());
	}
	
	if (ExecData.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetDamage(GetDamage());
	}
	
	if (ExecData.EvaluatedData.Attribute == GetHealingAttribute())
	{
		SetHealing(GetHealing());
	}
	
	if (ExecData.EvaluatedData.Attribute == GetRangeAttribute())
	{
		SetAttackSpeed(GetAttackSpeed());
	}
}
