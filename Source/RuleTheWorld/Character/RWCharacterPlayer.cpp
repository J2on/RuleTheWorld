// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterPlayer.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"


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


}


void ARWCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}


void ARWCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
}




