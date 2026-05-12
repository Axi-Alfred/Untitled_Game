#include "Shop.h"
#include "PlayerStats.h"
#include "Untitled_Game/DamageSystem/DamageSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UShop::UShop()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<FShopOffer> UShop::GetCurrentOffers(AActor* Player) const
{
	if (!Player)
	{
		return TArray<FShopOffer>();
	}

	if (UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>())
	{
		return Stats->CurrentShopOffers;
	}

	return TArray<FShopOffer>();
}

void UShop::GenerateOffers(AActor* Player)
{
	if (!UpgradeTable || !Player)
	{
		OnShopOffersChanged.Broadcast();
		return;
	}

	UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>();
	if (!Stats)
	{
		OnShopOffersChanged.Broadcast();
		return;
	}

	Stats->CurrentShopOffers.Empty();

	TArray<FName> RowNames = UpgradeTable->GetRowNames();
	TArray<FName> AvailableIds;

	for (const FName& RowName : RowNames)
	{
		const FShopUpgradeRow* Row = UpgradeTable->FindRow<FShopUpgradeRow>(RowName, TEXT("GenerateOffers"));

		if (!Row)
		{
			continue;
		}

		if (IsUpgradeAvailable(RowName, *Row, Stats))
		{
			AvailableIds.Add(RowName);
		}
	}

	for (int32 i = 0; i < NumberOfRandomOffers && AvailableIds.Num() > 0; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, AvailableIds.Num() - 1);
		const FName ChosenId = AvailableIds[RandomIndex];

		const FShopUpgradeRow* ChosenRow = UpgradeTable->FindRow<FShopUpgradeRow>(ChosenId, TEXT("GenerateOffers"));

		if (ChosenRow)
		{
			FShopOffer Offer;
			Offer.UpgradeId = ChosenId;
			Offer.UpgradeData = *ChosenRow;
			Stats->CurrentShopOffers.Add(Offer);
		}

		AvailableIds.RemoveAt(RandomIndex);
	}

	OnShopOffersChanged.Broadcast();
}

bool UShop::IsUpgradeAvailable(FName UpgradeId, const FShopUpgradeRow& Row, UPlayerStats* Stats) const
{
	if (!Stats)
	{
		return false;
	}

	if (!Row.bCanAppearInRandomShop)
	{
		return false;
	}

	if (Row.MaxPurchaseCount > 0 && Stats->GetPurchaseCount(UpgradeId) >= Row.MaxPurchaseCount)
	{
		return false;
	}

	if (!Row.RequiredUpgradeId.IsNone() && Stats->GetPurchaseCount(Row.RequiredUpgradeId) <= 0)
	{
		return false;
	}

	return true;
}

bool UShop::BuyOffer(int32 OfferIndex, AActor* Player)
{
	if (!Player)
	{
		return false;
	}

	UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>();
	if (!Stats || !Stats->CurrentShopOffers.IsValidIndex(OfferIndex))
	{
		return false;
	}

	const FShopOffer Offer = Stats->CurrentShopOffers[OfferIndex];

	if (!Stats->SpendPoints(Offer.UpgradeData.Cost))
	{
		return false;
	}

	ApplyUpgrade(Offer.UpgradeId, Offer.UpgradeData, Player);

	Stats->AddPurchase(Offer.UpgradeId);

	Stats->CurrentShopOffers.RemoveAt(OfferIndex);

	OnShopOffersChanged.Broadcast();

	return true;
}

bool UShop::RerollOffers(AActor* Player)
{
	if (!Player)
	{
		return false;
	}

	UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>();
	if (!Stats)
	{
		return false;
	}

	if (!Stats->SpendPoints(RerollCost))
	{
		return false;
	}

	GenerateOffers(Player);

	return true;
}

bool UShop::BuyHealthPotion(AActor* Player)
{
	if (!Player)
	{
		return false;
	}

	UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>();
	if (!Stats)
	{
		return false;
	}

	if (!Stats->SpendPoints(HealthPotionCost))
	{
		return false;
	}

	if (UDamageSystemComponent* Damage = Player->FindComponentByClass<UDamageSystemComponent>())
	{
		Damage->HandleIncomingHeal(HealthPotionHealAmount, Player);
	}

	return true;
}

bool UShop::BuyDefenseHeal(AActor* Player)
{
	if (!Player)
	{
		return false;
	}

	UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>();
	if (!Stats)
	{
		return false;
	}

	if (!Stats->SpendPoints(DefenseHealCost))
	{
		return false;
	}

	return true;
}

void UShop::ApplyUpgrade(FName UpgradeId, const FShopUpgradeRow& Row, AActor* Player)
{
	if (!Player)
	{
		return;
	}

	UPlayerStats* Stats = Player->FindComponentByClass<UPlayerStats>();

	switch (Row.UpgradeType)
	{
	case EShopUpgradeType::MaxHealth:
		{
			if (UDamageSystemComponent* Damage = Player->FindComponentByClass<UDamageSystemComponent>())
			{
				Damage->AddMaxHealth(Row.Value, true);
			}

			break;
		}

	case EShopUpgradeType::WeaponDamage:
		{
			if (Stats)
			{
				Stats->DamageMultiplier += Row.Value;
			}

			break;
		}

	case EShopUpgradeType::AttackSpeed:
		{
			if (Stats)
			{
				Stats->AttackSpeedMultiplier += Row.Value;
			}

			break;
		}

	case EShopUpgradeType::WeaponRange:
		{
			if (Stats)
			{
				Stats->RangeMultiplier += Row.Value;
			}

			break;
		}

	case EShopUpgradeType::MoveSpeed:
		{
			if (Stats)
			{
				Stats->MoveSpeedBonus += Row.Value;
			}

			if (ACharacter* Character = Cast<ACharacter>(Player))
			{
				if (Character->GetCharacterMovement())
				{
					Character->GetCharacterMovement()->MaxWalkSpeed += Row.Value;
				}
			}

			break;
		}

	case EShopUpgradeType::UnlockWeapon:
		{
			break;
		}

	default:
		break;
	}
}  