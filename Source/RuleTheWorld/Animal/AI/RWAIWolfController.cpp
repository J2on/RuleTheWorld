// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/AI/RWAIWolfController.h"

#include "BehaviorTree/BehaviorTree.h"

ARWAIWolfController::ARWAIWolfController()
{
	
	// Behavior Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeRef(TEXT("/Script/AIModule.BehaviorTree'/Game/RuleTheWorld/Animal/AI/BT/BT_Wolf.BT_Wolf'"));
	if(BehaviorTreeRef.Object)
	{
		BehaviorTreeAsset = BehaviorTreeRef.Object;
	}
	
}

void ARWAIWolfController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* TempBlackBoard = Blackboard.Get(); 
	if(UseBlackboard(BlackboardAsset, TempBlackBoard))
	{
		if(!RunBehaviorTree(BehaviorTreeAsset))
		{
			UE_LOG(LogTemp, Error, TEXT("Wolf AI Controller : BehaviorTree is not Running"));
		}
		
		BlackboardComponent = GetBlackboardComponent();
		
		
	}

	
}

