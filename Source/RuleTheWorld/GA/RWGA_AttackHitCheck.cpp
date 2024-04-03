// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/RWGA_AttackHitCheck.h"

URWGA_AttackHitCheck::URWGA_AttackHitCheck()
{
	// Instancing Option
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void URWGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled); 

	UE_LOG(LogTemp, Log, TEXT("RWGA_AHC"));
}
