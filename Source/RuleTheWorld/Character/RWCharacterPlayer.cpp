// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterPlayer.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/RWPlayerState.h"
#include "AbilitySystemComponent.h"


ARWCharacterPlayer::ARWCharacterPlayer()
{
	// Spring Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// GAS
	// ASC is bring from PlayerState at PossessedBy()
	ASC = nullptr;
}

UAbilitySystemComponent* ARWCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void ARWCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}


void ARWCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
}

void ARWCharacterPlayer::PossessedBy(AController* NewController)
{

	Super::PossessedBy(NewController);
	ARWPlayerState* RWPS = GetPlayerState<ARWPlayerState>();

	
	if(RWPS)
	{
		ASC = RWPS->GetAbilitySystemComponent();
		
		// Owner Actor와 Avatar Actor가 정해졌으니 초기화
		ASC->InitAbilityActorInfo(RWPS, this);
		

		for(const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}
		
		APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}



