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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

		
// Network
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable)
	void ServerRequestTimeVariable();
	
	UPROPERTY(BlueprintReadOnly, Category = "Network")
	FTimerHandle TimerHandle_RequestMyVariable;

	void RequestTimeVariableFromServer();

	// Time Variable
	UFUNCTION(Client, Reliable)
	void UpdateTime(float DeltaSeconds);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 DayScore;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Time")
	float CurrentTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Time")
	float DayProgressPercent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentHour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Day, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentMinute;

public:
	float GetClientCurrentTime() const;
	float GetClientDayProgressPercent() const;
	int32 GetClientDayScore() const;
};
