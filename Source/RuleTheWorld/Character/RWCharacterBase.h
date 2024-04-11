// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RWCharacterBase.generated.h"

UCLASS()
class RULETHEWORLD_API ARWCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARWCharacterBase();

// Item
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	TObjectPtr<class UBoxComponent> CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	TObjectPtr<class ARWInteractableActor> CollisionedItem;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item")
	uint8 bIsItemInBound:1;
	
};
