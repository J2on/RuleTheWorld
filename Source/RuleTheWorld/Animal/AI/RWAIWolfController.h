// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RWAIWolfController.generated.h"

/**
 * 
 */
UCLASS()
class RULETHEWORLD_API ARWAIWolfController : public AAIController
{
	GENERATED_BODY()

public:
	ARWAIWolfController();

	virtual void OnPossess(APawn* InPawn) override;

// BehaviorTree
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BT)
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BT)
	TObjectPtr<UBlackboardData> BlackboardAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BT)
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BT)
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BT)
	TObjectPtr<class UBlackboardComponent> BlackboardComponent;	

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
