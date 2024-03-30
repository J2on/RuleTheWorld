// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "RWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RULETHEWORLD_API ARWPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARWPlayerController();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
public:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

// Character
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ARWCharacterPlayer> PlayerPawn;
	
// Input System
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> EnableLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> RunAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category =  Input, Meta = (AllowPrivateAccess = "True"))
	TObjectPtr<class UInputAction> SneakingAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EnableLook(const FInputActionValue& Value);
	void DisableLook(const FInputActionValue& Value);
	void ControllerJump(const FInputActionValue& Value);
	void ControllerStopJumping(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void StopRunning(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Sneaking(const FInputActionValue& Value);
	void StopSneaking(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "True"))
	uint8 bIsEnableLook:1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "True"))
	uint8 bIsRunning:1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "True"))
	uint8 bIsSneaking:1;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	
	// 처음부터 부여할 어빌리티dml 목록 <- 내용물은 블루프린트에서 설정
	UPROPERTY(EditAnywhere, Category=GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category=GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	
	/* Input 보류
	void SetupGasInputComponent();
	void GasInputPressed(int32 InputID);
	void GasInputReleased(int32 InputID);
	*/
	
// Combo Attack Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboAttackMontage; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class URWComboAttackData> ComboAttackData; 
	
	
	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	// Local Variable
	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	uint8 bHasNextComboCommand:1 = false;
};
