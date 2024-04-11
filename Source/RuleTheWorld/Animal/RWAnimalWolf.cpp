// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/RWAnimalWolf.h"

#include "AI/RWAIWolfController.h"

ARWAnimalWolf::ARWAnimalWolf()
{
	PrimaryActorTick.bCanEverTick = true;
	
	
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
