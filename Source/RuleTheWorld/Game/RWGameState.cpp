// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWGameState.h"
#include "Game/RWGameMode.h"
#include "Net/UnrealNetwork.h"



constexpr float START_TIME_CLIENT = 120.f; // Game Start 06:00 
constexpr float ONE_DAY_CLIENT = 480.f; // 8min(Real Time) = 1Day / 1min = 3Hours / 20sec = 1Hour
constexpr int ONE_HOUR_CLIENT = 20;

ARWGameState::ARWGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	// Initialize
	DayScore = 0;
	CurrentTime = 0.f;
	DayProgressPercent = 0.f;
	CurrentHour = 0;
	CurrentMinute = 0;
}

void ARWGameState::BeginPlay()
{
	Super::BeginPlay();
	// BeginPlay 시에 Server에서 Time 관련된 변수들을 초기화해준다. 
	RequestTimeVariableFromServer();
}

void ARWGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);	
	UpdateTime(DeltaSeconds);
}

void ARWGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARWGameState, CurrentTime);
	DOREPLIFETIME(ARWGameState, DayProgressPercent);
	DOREPLIFETIME(ARWGameState, DayScore);
}

// 클라이언트에서 서버로 변수를 요청하는 함수를 정의합니다.
// RPC로 요청을 보내는 함수
void ARWGameState::RequestTimeVariableFromServer()
{
	// 서버에 함수 호출을 요청합니다.
	if (GetNetMode() != NM_DedicatedServer) // 서버에서는 호출하지 않도록합니다.
	{
		// 실질적으로 서버에서 실행되는 함수
		ServerRequestTimeVariable();
	}
	// 게임시간 하루 마다 실행되어 최신화
	GetWorldTimerManager().SetTimer(TimerHandle_RequestMyVariable, this, &ARWGameState::RequestTimeVariableFromServer, ONE_DAY_CLIENT, true);
}

float ARWGameState::GetClientCurrentTime() const
{
	return CurrentTime;
}

float ARWGameState::GetClientDayProgressPercent() const
{
	return DayProgressPercent;
}

int32 ARWGameState::GetClientDayScore() const
{
	return DayScore;
}

// Client Only
void ARWGameState::UpdateTime_Implementation(float DeltaSeconds)
{
	CurrentTime += DeltaSeconds;
	// Day Change
	if(CurrentTime >= ONE_DAY_CLIENT)
	{
		DayScore++;
		CurrentTime -= ONE_DAY_CLIENT;
		UE_LOG(LogTemp, Log, TEXT("Game State - Day : %d CurrentTime : %f ProgressPercent : %f"), DayScore, CurrentTime, DayProgressPercent);
	}
	// 하루가 얼마나 지났는지 퍼센트로 표시
	DayProgressPercent = 100 * (CurrentTime / ONE_DAY_CLIENT);
	CurrentHour = CurrentTime / ONE_HOUR_CLIENT;
	CurrentMinute = ((60/ONE_HOUR_CLIENT) * static_cast<int32>(CurrentTime)) % 60;
}

// 서버에서 변수를 전송하는 함수를 구현합니다.
void ARWGameState::ServerRequestTimeVariable_Implementation()
{
	// 클라이언트에서 실행됩니다.
	// 서버에서 처리할 코드를 작성합니다.
	// 이 부분에서 GameMode로부터 정보를 가져오고, 클라이언트에게 전송할 수 있습니다.

	// Get Time Variable
	TObjectPtr<ARWGameMode> GameMode = Cast<ARWGameMode>(GetWorld()->GetAuthGameMode());
	CurrentTime = GameMode->GetCurrentTime();
	DayProgressPercent = GameMode->GetDayProgressPercent();
	DayScore = GameMode->GetDayScore();
}