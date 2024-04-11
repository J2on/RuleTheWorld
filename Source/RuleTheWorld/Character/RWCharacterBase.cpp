// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Object/RWInteractableActor.h"

// Sets default values
ARWCharacterBase::ARWCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn의 Rotation?
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;


	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 420.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.f,0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	// Assign Mesh Reference 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/survivor_man/Mesh/Survivor_man_3/SK_Survivor_man_3_NoCloth.SK_Survivor_man_3_NoCloth'"));
	if(CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	// Anim Instance Assign
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/RuleTheWorld/Character/Animation/ABP_RWChracter.ABP_RWChracter_C"));
	if(AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// Item
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARWCharacterBase::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ARWCharacterBase::OnOverlapEnd);
	CollisionBox->SetupAttachment(RootComponent);
	CollisionedItem = nullptr;
	bIsItemInBound = false;
}

void ARWCharacterBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 잡고있는 item이 없고, RWInteractableActor인 경우
	ARWInteractableActor* OtherInteractableActor = Cast<ARWInteractableActor>(OtherActor);
	if(OtherInteractableActor && CollisionedItem == nullptr)
	{
		CollisionedItem = OtherInteractableActor;
		bIsItemInBound = true;
	}
}

void ARWCharacterBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CollisionedItem = nullptr;
	bIsItemInBound = false;
}




