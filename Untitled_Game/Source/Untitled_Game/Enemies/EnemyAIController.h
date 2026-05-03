
#pragma once

#include "CoreMinimal.h"
#include "ObjectiveManager.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class UNTITLED_GAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	// Området som fienden kan hitta spelaren inom
	UPROPERTY(EditAnywhere, Category = "AI")
	float DetectionRadius = 800.f;
	
	// Behavior tree som används utav fienden
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
private:
	
	// referens till player
	UPROPERTY()
	AActor* PlayerActor = nullptr;
	
	// Referens till ObjectiveManager
	UPROPERTY()
	AObjectiveManager* ObjectiveManager = nullptr;
	
	// Updaterar fiendens target (player eller objective)
	void UpdateTarget();
	
	// Blackboard key för nuvarande target (används i MoveTo)
	static constexpr const TCHAR* TargetActorKey = TEXT("TargetActor");
};
