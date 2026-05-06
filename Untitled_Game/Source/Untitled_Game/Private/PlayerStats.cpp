#include "PlayerStats.h"

UPlayerStats::UPlayerStats()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UPlayerStats::CanAfford(int32 Cost) const
{
	return Points >= Cost;
}

bool UPlayerStats::SpendPoints(int32 Cost)
{
	if (!CanAfford(Cost))
	{
		return false;
	}

	Points -= Cost;
	OnPointsChanged.Broadcast(Points);
	return true;
}

void UPlayerStats::AddPoints(int32 Amount)
{
	Points += Amount;
	OnPointsChanged.Broadcast(Points);
}

int32 UPlayerStats::GetPurchaseCount(FName UpgradeId) const
{
	if (const int32* Count = PurchaseCounts.Find(UpgradeId))
	{
		return *Count;
	}

	return 0;
}

void UPlayerStats::AddPurchase(FName UpgradeId)
{
	int32& Count = PurchaseCounts.FindOrAdd(UpgradeId);
	Count++;
}