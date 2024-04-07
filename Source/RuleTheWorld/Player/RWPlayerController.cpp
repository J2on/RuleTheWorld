// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

#include "Character/RWCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

constexpr int32 MaxCombo = 3;

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

	ComboAttackMontages = {ComboAttackMontage1, ComboAttackMontage2, ComboAttackMontage3, ComboAttackMontage4};
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
		ComboAction();
	}
	else
	{
		bHasNextComboCommand = true;
	}
}

void ARWPlayerController::ComboAction()
{
	// Movement Setting
	PlayerPawn->GetCharacterMovement()->SetMovementMode(MOVE_None);

	// Animation Setting
	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = PlayerPawn->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboAttackMontages[CurrentCombo], AttackSpeedRate);
	
	bHasNextComboCommand = false;
	
	// Combo Status
	float RateTime; 
	if(CurrentCombo == MaxCombo)
	{
		CurrentCombo = 1;
		RateTime = 1.5f;
	}
	else
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, MaxCombo);
		RateTime = 1.0f;
	}
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ARWPlayerController::CheckInput, RateTime, false);
}

void ARWPlayerController::CheckInput()
{
	AttackTimerHandle.Invalidate();
	PlayerPawn->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	// Non Attack
	if(!bHasNextComboCommand)
	{
		CurrentCombo = 0;
	}
	else // Next Attack
	{
		bHasNextComboCommand = false;
		ComboAction();
	}
}
