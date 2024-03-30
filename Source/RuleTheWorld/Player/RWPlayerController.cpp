// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "RWPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Character/RWCharacterPlayer.h"
#include "Character/RWComboAttackData.h"
#include "GameFramework/CharacterMovementComponent.h"


ARWPlayerController::ARWPlayerController()
{
	//Input
	bIsEnableLook = false;
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/RuleTheWorld/Input/IMC_Default.IMC_Default'"));
	if(nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_Move.IA_Move'"));
	if(nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_Jump.IA_Jump'"));
	if(nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_Look.IA_Look'"));
	if(nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionEnableLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_EnableLook.IA_EnableLook'"));
	if(nullptr != InputActionEnableLookRef.Object)
	{
		EnableLookAction = InputActionEnableLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRunRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_Run.IA_Run'"));
	if(nullptr != InputActionRunRef.Object)
	{
		RunAction = InputActionRunRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_Attack.IA_Attack'"));
	if(nullptr != InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSneakingRef(TEXT("/Script/EnhancedInput.InputAction'/Game/RuleTheWorld/Input/Action/IA_Sneaking.IA_Sneaking'"));
	if(nullptr != InputActionSneakingRef.Object)
	{
		SneakingAction = InputActionSneakingRef.Object;
	}
	
	// GAS
	ASC = nullptr;
}

UAbilitySystemComponent* ARWPlayerController::GetAbilitySystemComponent() const
{
	return ASC;
}

void ARWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 게임 시작과 동시에 마우스 인풋을 게임 내부로 이동시키기
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Player
	PlayerPawn = CastChecked<ARWCharacterPlayer>(GetPawn());
	
}

void ARWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// 함수와 바인딩
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARWPlayerController::ControllerJump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARWPlayerController::ControllerStopJumping);
	EnhancedInputComponent->BindAction(EnableLookAction, ETriggerEvent::Triggered, this, &ARWPlayerController::EnableLook);
	EnhancedInputComponent->BindAction(EnableLookAction, ETriggerEvent::Completed, this, &ARWPlayerController::DisableLook);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARWPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARWPlayerController::Look);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ARWPlayerController::Run);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ARWPlayerController::StopRunning);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ARWPlayerController::Attack);
	EnhancedInputComponent->BindAction(SneakingAction, ETriggerEvent::Triggered, this, &ARWPlayerController::Sneaking);
	EnhancedInputComponent->BindAction(SneakingAction, ETriggerEvent::Completed, this, &ARWPlayerController::StopSneaking);

	/*if(IsValid(ASC) && IsValid(InputComponent))
	{// 플레이어의 input Component가 EnhancedInput인지 확인
		//EnhancedInput은 InputId(마지막 요소)를 통해 추가적인 정보를 전달해 줄 수 있음, 위에 PossessedBy 함수에서 각 어빌리티 마다의 Id정보를 할당해서 각 입력마다 다른 함수가 작동하도록 함
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARWPlayerController::GasInputPressed, 0); 
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARWPlayerController::GasInputReleased, 0);
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ARWPlayerController::GasInputPressed, 1);
	}*/
}

void ARWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ARWPlayerState* RWPS = GetPlayerState<ARWPlayerState>();

	if(RWPS)
	{
		ASC = RWPS->GetAbilitySystemComponent();
		// Owner Actor와 Avatar Actor가 정해졌으니 초기화
		ASC->InitAbilityActorInfo(RWPS, this);
		
		// 어빌리티 마다의 IUnput ID 부여 
		
		for(const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}
		
		/* Input 보류
		for(const auto& StartInputAbility : StartInputAbilities) // 초기 어빌리티 부여
		{
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = StartInputAbility.Key; // Key 값이 입력번호로 설정됨
			ASC->GiveAbility(StartSpec);
		}
		*/

		SetupInputComponent(); // 서버에서 Input Component 바인딩
		// 강의에서 SetupGasInputComponent()를 만들어 사용했지만, 기존 함수를 사용해 봄.

		ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void ARWPlayerController::Move(const FInputActionValue& Value)
{
	// Input Value
	FVector2D MovementVector = Value.Get<FVector2D>(); 

	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// X, Y Move Value
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(MovementVector.X && MovementVector.Y) // 대각 이동 시 속도 조절
	{
		MovementVector.X *= 0.75;
		MovementVector.Y *= 0.75;
	}

	// Using Movement Component
	
	if(bIsSneaking)
	{
		MovementVector.X *= 0.2;
		MovementVector.Y *= 0.2;
	}
	else if(!bIsRunning) // Running이 아닐때는 절반의 속도
	{
		MovementVector.X *= 0.5;
		MovementVector.Y *= 0.5;
	}
	
	
	PlayerPawn->AddMovementInput(ForwardDirection, MovementVector.X);
	PlayerPawn->AddMovementInput(RightDirection, MovementVector.Y);
}

void ARWPlayerController::Look(const FInputActionValue& Value)
{
	if(bIsEnableLook) 
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();
	
		this->AddYawInput(LookAxisVector.X);
		this->AddPitchInput(LookAxisVector.Y);
	}
	     
}

void ARWPlayerController::EnableLook(const FInputActionValue& Value)
{
	bIsEnableLook = true;
}

void ARWPlayerController::DisableLook(const FInputActionValue& Value)
{
	bIsEnableLook = false;
}

void ARWPlayerController::ControllerJump(const FInputActionValue& Value)
{
	PlayerPawn->Jump();
}

void ARWPlayerController::ControllerStopJumping(const FInputActionValue& Value)
{
	PlayerPawn->StopJumping();
}

void ARWPlayerController::Run(const FInputActionValue& Value)
{
	bIsRunning = true;
}

void ARWPlayerController::StopRunning(const FInputActionValue& Value)
{
	bIsRunning = false;
}

void ARWPlayerController::Attack(const FInputActionValue& Value)
{
	ProcessComboCommand();
}

void ARWPlayerController::Sneaking(const FInputActionValue& Value)
{
	bIsSneaking = true;
}

void ARWPlayerController::StopSneaking(const FInputActionValue& Value)
{
	bIsSneaking = false;
}

void ARWPlayerController::ProcessComboCommand()
{
	if(CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if(!ComboTimerHandle.IsValid())
	{
		bHasNextComboCommand = false;
	}
	else
	{
		bHasNextComboCommand = true;
	}
}

void ARWPlayerController::ComboActionBegin()
{
	// Combo Status
	CurrentCombo = 1;

	// Movement Setting
	PlayerPawn->GetCharacterMovement()->SetMovementMode(MOVE_None);

	// Animation Setting
	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = PlayerPawn->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboAttackMontage, AttackSpeedRate);

	// Delegate
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ARWPlayerController::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboAttackMontage);

	// Timer Start
	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void ARWPlayerController::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	PlayerPawn->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ARWPlayerController::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboAttackData->EffectiveFrameCount.IsValidIndex(ComboIndex));
	const float AttackSppedRate = 1.0f;
	float ComboEffectiveTime = (ComboAttackData->EffectiveFrameCount[ComboIndex] / ComboAttackData->FrameRate) / AttackSppedRate;
	if(ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ARWPlayerController::ComboCheck, ComboEffectiveTime, false);
	}
}

void ARWPlayerController::ComboCheck()
{
	ComboTimerHandle.Invalidate(); // 초기화
	if(bHasNextComboCommand)
	{
		UAnimInstance* AnimInstance = PlayerPawn->GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboAttackData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboAttackData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);
		SetComboCheckTimer();
		bHasNextComboCommand = false;
	}
}
