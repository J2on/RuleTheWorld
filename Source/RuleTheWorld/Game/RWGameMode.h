// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RWGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RULETHEWORLD_API ARWGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARWGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
// Game Time
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	float CurrentTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	float DayProgressPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 DayScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentHour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentMinute;
	
	void UpdateDate(float DeltaSeconds);

public:
	float GetCurrentTime() const;
	float GetDayProgressPercent() const;
	int32 GetDayScore() const;

// Spawn Animal And Plant
private:
	UPROPERTY(EditAnywhere, Category = Animal)
	TSubclassOf<class ARWAnimalWolf> WolfClass;
	
	void SpawnWolf();
	void UpdateMaxWolfNum();
	
	int MaxWolfNum;
	int CurrentWolfNum;

public:
	// 사냥 시 현재 수를 줄여줌
	void DecreaseCurrentWolfNum();
};

