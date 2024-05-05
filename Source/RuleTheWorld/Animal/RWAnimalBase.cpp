// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/RWAnimalBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARWAnimalBase::ARWAnimalBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(50.f,50.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -50.0f), FRotator(0.0f, -90.f,0.0f));
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// AI Controller Possess
	// AIControllerClass <- BP에서 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ARWAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARWAnimalBase::UpdateWalkSpeed(float WalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}




