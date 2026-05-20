
#pragma once

#include "CoreMinimal.h"
#include "ObjectiveManager.h"
#include "AIController.h"
#include "TowerEnemyAIController.generated.h"

UCLASS()
class UNTITLED_GAME_API ATowerEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	// Behavior tree som används utav fienden
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
private:
	
	// Referens till ObjectiveManager
	UPROPERTY()
	AObjectiveManager* ObjectiveManager = nullptr;
	
	// Updaterar fiendens target (objective)
	void UpdateTarget();
	
	// Blackboard key för nuvarande target (används i MoveTo)
	static constexpr const TCHAR* TargetActorKey = TEXT("TargetActor");
};