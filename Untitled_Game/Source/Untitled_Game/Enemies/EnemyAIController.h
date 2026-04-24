// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectiveManager.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_GAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	float DetectionRadius = 800.f;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
private:
	AActor* PlayerActor;
	AObjectiveManager* ObjectiveManager;
	
	void UpdateTarget();
	
};
