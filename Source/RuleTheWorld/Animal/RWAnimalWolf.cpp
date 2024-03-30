// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/RWAnimalWolf.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/RWAIWolfController.h"

ARWAnimalWolf::ARWAnimalWolf()
{
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

	
	// Assign Mesh Reference 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AnimalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'"));
	if(AnimalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(AnimalMeshRef.Object);
	}

	// AI Controller Possess
	AIControllerClass = ARWAIWolfController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
