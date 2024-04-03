// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWGameState.h"

constexpr float StartTime = 120.f; // Game Start 06:00 
constexpr float OneDay = 480.f; // 8min(Real Time) = 1Day / 1min = 3Hours / 20sec = 1Hour

ARWGameState::ARWGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	// Day
	CurrentTime = StartTime;
	DayScore = 1;
	DayProgressPercent = StartTime / OneDay;

}

void ARWGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateDate(DeltaSeconds);
}

float ARWGameState::GetDayProgressPercent()
{
	return DayProgressPercent;
}

void ARWGameState::UpdateDate(float DeltaSeconds)
{
	CurrentTime += DeltaSeconds;
	// Day Change
	if(CurrentTime >= OneDay)
	{
		DayScore++;
		CurrentTime -= OneDay;
		UE_LOG(LogTemp, Log, TEXT("Game State - Day : %d CurrentTime : %f ProgressPercent : %f"), DayScore, CurrentTime, DayProgressPercent);
	}
	// 하루가 얼마나 지났는지 퍼센트로 표시
	DayProgressPercent = 100 * (CurrentTime / OneDay);
}


