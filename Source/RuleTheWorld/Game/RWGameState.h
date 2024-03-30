// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RWGameState.generated.h"

/**
 * 
 */

UCLASS()
class RULETHEWORLD_API ARWGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ARWGameState();

	virtual void Tick(float DeltaSeconds) override;

	float GetDayProgressPercent();

// Day and Night
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Day)
	float CurrentTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Day)
	float DayProgressPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Day)
	int32 DayScore;

	void UpdateDate(float DeltaSeconds);

};
