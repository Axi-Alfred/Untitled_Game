#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	// Hämta player(s)
	PlayerOneActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	// Om player 2 existerar 
	if (UGameplayStatics::GetPlayerPawn(GetWorld(), 1))
	{
		PlayerTwoActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 1);
	}
	
	// Hämta manager
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveManager::StaticClass(), FoundManagers);
	
	if (FoundManagers.Num() > 0)
	{
		ObjectiveManager = Cast<AObjectiveManager>(FoundManagers[0]);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdatePlayers();
	UpdateTarget();
}

void AEnemyAIController::UpdateTarget()
{
	if (!GetPawn() || !ObjectiveManager) return;
	
	AActor* CurrentObjective = ObjectiveManager->GetCurrentObjective();
	if (!CurrentObjective) return;
	
	AActor* ClosestPlayer = nullptr;
	float ClosestDistance = DetectionRadius;
	
	//Check för player 1
	if (PlayerOneActor)
	{
		float Distance = FVector::Dist(
			GetPawn()->GetActorLocation(),
			PlayerOneActor->GetActorLocation());
		
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestPlayer = PlayerOneActor;
		}
	}
	
	//Check för player 2
	if (PlayerTwoActor)
	{
		float Distance = FVector::Dist(
			GetPawn()->GetActorLocation(),
			PlayerTwoActor->GetActorLocation());
		
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestPlayer = PlayerTwoActor;
		}
	}
	
	// Om en player hittades inom radius = target player
	// annars = target objective
	AActor* NewTarget = ClosestPlayer ? ClosestPlayer : CurrentObjective;
	
	// uppdaterar blackboard och sätt ny target
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		AActor* CurrentBBTarget = Cast<AActor>(BB->GetValueAsObject(TargetActorKey));
		
		if (CurrentBBTarget != NewTarget)
		{
			BB->SetValueAsObject(TargetActorKey, NewTarget);
			StopMovement();
		}
	}
}

void AEnemyAIController::UpdatePlayers()
{
	if (!PlayerOneActor)
	{
		PlayerOneActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
	
	if (!PlayerTwoActor)
	{
		PlayerTwoActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 1);
	}
}