// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/AI/RWAIWolfController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

ARWAIWolfController::ARWAIWolfController()
{
	
	// Behavior Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeRef(TEXT("/Script/AIModule.BehaviorTree'/Game/RuleTheWorld/Animal/AI/BT/BT_Wolf.BT_Wolf'"));
	if(BehaviorTreeRef.Object)
	{
		BehaviorTreeAsset = BehaviorTreeRef.Object;
	}
	// Black Board
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackBoardRef(TEXT("/Script/AIModule.BlackboardData'/Game/RuleTheWorld/Animal/AI/BB/BB_Wolf.BB_Wolf'"));
	if(BlackBoardRef.Object)
	{
		BlackboardAsset = BlackBoardRef.Object;
	}
}

void ARWAIWolfController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComponent = Blackboard.Get(); 
	if(UseBlackboard(BlackboardAsset, BlackboardComponent))
	{
		if(!RunBehaviorTree(BehaviorTreeAsset))
		{
			UE_LOG(LogTemp, Error, TEXT("Wolf : BehaviorTree is not Running"));
		}
	}
}
