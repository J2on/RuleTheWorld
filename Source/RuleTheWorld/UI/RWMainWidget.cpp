// Fill out your copyright notice in the Description page of Project Settings.


#include "RWMainWidget.h"

#include "Character/RWCharacterPlayer.h"
#include "Components/Image.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

URWMainWidget::URWMainWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	bIsMinimapCompleted = false;
}

void URWMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URWMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Native Construct에서 실행하는 경우에 캐릭터의 생성보다 일찍 호출되어 설정이 안되는 경우가 생겼다.
	// 이를 위해 임시방편으로 설정 완료 시에는 bool 형으로 막아두는 형태로 구현
	if(!bIsMinimapCompleted)
	{
		SetMinimapMaterial();
	}
}

void URWMainWidget::SetMinimapMaterial()
{
	// Content 폴더 내의 메테리얼 경로
	FString MaterialPath = "/Game/RuleTheWorld/UI/M_Minimap.M_Minimap";
	
	// 메테리얼을 로드
	MinimapMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, *MaterialPath));
	
	// 메테리얼 인스턴스를 생성하고 원하는 메테리얼을 지정
	MinimapMaterialInstance = UMaterialInstanceDynamic::Create(MinimapMaterial, this);
	
	ARWCharacterPlayer* CharacterPlayer = Cast<ARWCharacterPlayer>(GetOwningPlayerPawn());
	
	if(CharacterPlayer)
	{
		// 캐릭터의 SceneCapture에서 TextureRenderTarget을 받아와 Material의 Parameter에 배정
		UTextureRenderTarget2D* MinimapTexture = CharacterPlayer->MiniMapSceneCapture->TextureTarget;
		if(MinimapTexture)
		{
			MinimapMaterialInstance->SetTextureParameterValue("Minimap", MinimapTexture);
			// 이미지 바인딩	
			MinimapImage = Cast<UImage>(GetWidgetFromName(TEXT("Minimap")));
			if(MinimapImage)
			{
				MinimapImage->SetBrushFromMaterial(MinimapMaterialInstance);

				// Minimap 설정의 모든 작업이 끝났을 때, 해당 변수를 True로 변경
				bIsMinimapCompleted = true;
			}
		}
	}
}

