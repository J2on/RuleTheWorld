// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/RWAnimalPig.h"

ARWAnimalPig::ARWAnimalPig()
{
	// Assign Mesh Reference 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AnimalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/AnimalVarietyPack/Pig/Meshes/SK_Pig.SK_Pig'"));
	if(AnimalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(AnimalMeshRef.Object);
	}
}
