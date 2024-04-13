// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RWGameMode.h"

#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "Player/RWPlayerController.h"

constexpr float StartTime = 120.f; // Game Start 06:00 
constexpr float OneDay = 480.f; // 8min(Real Time) = 1Day / 1min = 3Hours / 20sec = 1Hour

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
	CurrentTime = StartTime;
	DayScore = 1;
	DayProgressPercent = StartTime / OneDay;
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
	if(CurrentTime >= OneDay)
	{
		DayScore++;
		CurrentTime -= OneDay;
		UE_LOG(LogTemp, Log, TEXT("Game State - Day : %d CurrentTime : %f ProgressPercent : %f"), DayScore, CurrentTime, DayProgressPercent);
	}
	// 하루가 얼마나 지났는지 퍼센트로 표시
	DayProgressPercent = 100 * (CurrentTime / OneDay);
}
