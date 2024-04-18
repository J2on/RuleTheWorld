// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RWGameMode.h"

#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "Player/RWPlayerController.h"

constexpr float START_TIME = 120.f; // Game Start 06:00 
constexpr float ONE_DAY = 480.f; // 8min(Real Time) = 1Day / 1min = 3Hours / 20sec = 1Hour
constexpr int ONE_HOUR = 20;

ARWGameMode::ARWGameMode()
{
	//DefaultPawnClass <- 해야 함
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/RuleTheWorld.RWCharacterPlayer"));
	static  ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/RuleTheWorld/Character/BP_RWCharacterPlayer.BP_RWCharacterPlayer_C"));
	if(DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	
	// Set PlayerController 
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/RuleTheWorld/Character/BP_RWPlayerController.BP_RWPlayerController_C"));
	if(PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	// Set GameState
	static ConstructorHelpers::FClassFinder<AGameStateBase> GameStateClassRef(TEXT("/Script/RuleTheWorld.RWGameState"));
    if(GameStateClassRef.Class)
    {
    	GameStateClass = GameStateClassRef.Class;
    }

	// Set PlayerState
	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateClassRef(TEXT("/Script/RuleTheWorld.RWPlayerState"));
	if(PlayerStateClassRef.Class)
	{
		PlayerStateClass = PlayerStateClassRef.Class;
	}
	
	// Day
	CurrentTime = START_TIME;
	DayScore = 1;
	DayProgressPercent = START_TIME / ONE_DAY;
}

void ARWGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		
	UpdateDate(DeltaSeconds);
}

void ARWGameMode::UpdateDate(float DeltaSeconds)
{
	CurrentTime += DeltaSeconds;
	// Day Change
	if(CurrentTime >= ONE_DAY)
	{
		DayScore++;
		CurrentTime -= ONE_DAY;
		UE_LOG(LogTemp, Log, TEXT("Game State - Day : %d CurrentTime : %f ProgressPercent : %f"), DayScore, CurrentTime, DayProgressPercent);
	}
	// 하루가 얼마나 지났는지 퍼센트로 표시
	DayProgressPercent = 100 * (CurrentTime / ONE_DAY);
	CurrentHour = CurrentTime / ONE_HOUR;
	CurrentMinute = ((60/ONE_HOUR) * static_cast<int32>(CurrentTime)) % 60;
}

float ARWGameMode::GetCurrentTime() const
{
	return CurrentTime;
}

float ARWGameMode::GetDayProgressPercent() const
{
	return DayProgressPercent;
}

int32 ARWGameMode::GetDayScore() const
{
	return DayScore;
}


