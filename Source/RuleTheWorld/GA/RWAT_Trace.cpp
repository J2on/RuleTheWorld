// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/RWAT_Trace.h"

URWAT_Trace::URWAT_Trace()
{
}

URWAT_Trace* URWAT_Trace::CreateTask(UGameplayAbility* OwningAbility)
{
	URWAT_Trace* NewTask = NewAbilityTask<URWAT_Trace>(OwningAbility);
	return NewTask;
}

void URWAT_Trace::Activate()
{
	Super::Activate();

	// 끝내는 부분
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
	EndTask();
}

void URWAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
