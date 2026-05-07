#include "ShopActor.h"
#include "Shop.h"
#include "PlayerStats.h"
#include "Components/BoxComponent.h"

AShopActor::AShopActor()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	RootComponent = InteractionBox;

	ShopComponent = CreateDefaultSubobject<UShop>(TEXT("ShopComponent"));

	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionBox->SetGenerateOverlapEvents(true);
	
}

void AShopActor::BeginPlay()
{

	Super::BeginPlay();

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AShopActor::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AShopActor::OnOverlapEnd);
	
}

bool AShopActor::IsPlayerInRange(AActor* Player) const
{
	return Player && Player == PlayerInRange;
	
	
}

void AShopActor::PrepareShopForPlayer(AActor* Player)
{
	if (!IsPlayerInRange(Player))
	{
		return;
		
	}

	if (ShopComponent)
	{
		ShopComponent->GenerateOffers(Player);
	}
}

void AShopActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->FindComponentByClass<UPlayerStats>())
	{
		PlayerInRange = OtherActor;
	}
}

void AShopActor::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	if (PlayerInRange == OtherActor)
	{
		PlayerInRange = nullptr;
	}
}  