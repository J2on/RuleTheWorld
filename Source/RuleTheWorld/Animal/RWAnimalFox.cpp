// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal/RWAnimalFox.h"

ARWAnimalFox::ARWAnimalFox()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AnimalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'"));
	if(AnimalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(AnimalMeshRef.Object);
	}
	
}
