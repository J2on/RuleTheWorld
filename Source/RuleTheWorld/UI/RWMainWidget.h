// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RWMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class RULETHEWORLD_API URWMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	URWMainWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minimap")
	TObjectPtr<class UImage> MinimapImage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minimap")
	TObjectPtr<class UMaterial> MinimapMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minimap")
	TObjectPtr<class UMaterialInstanceDynamic> MinimapMaterialInstance;

	void SetMinimapMaterial();
	
	uint8 bIsMinimapCompleted;
};
