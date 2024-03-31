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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	float CurrentTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	float DayProgressPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 DayScore;

	void UpdateDate(float DeltaSeconds);

};
