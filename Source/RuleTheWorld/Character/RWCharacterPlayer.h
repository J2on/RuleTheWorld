// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterBase.h"
#include "RWCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class RULETHEWORLD_API ARWCharacterPlayer : public ARWCharacterBase
{
	GENERATED_BODY()

public:
	ARWCharacterPlayer();
	
protected:
	virtual void BeginPlay() override;
	// Multiplay
	virtual void OnRep_PlayerState() override;
//Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
};
