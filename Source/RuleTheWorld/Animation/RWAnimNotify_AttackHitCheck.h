// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTags.h"
#include "RWAnimNotify_AttackHitCheck.generated.h"

/**
 * GAS
 */
UCLASS()
class RULETHEWORLD_API URWAnimNotify_AttackHitCheck : public UAnimNotify
{
	GENERATED_BODY()

public:
	URWAnimNotify_AttackHitCheck();

protected:
	virtual FString GetNotifyName_Implementation() const override; // 이름을 지정
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag TriggerGamePlayTag;
};
