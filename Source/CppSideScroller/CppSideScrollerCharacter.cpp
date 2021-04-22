// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CppSideScrollerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "CppSideScrollerGameState.h"
#include "CppSideScrollerGameMode.h"

#pragma optimize("", off)

ACppSideScrollerCharacter::ACppSideScrollerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	JumpMaxCount = 2;
	MaxHealth = 10.0F;
	MinFallDamageHeight = 500.0F;
	FallDamageMultiplier = 0.01F;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ACppSideScrollerCharacter::ModifyHealth(float healthModification)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + healthModification, 0.0F, MaxHealth);
	if (CurrentHealth <= 0.0F)
	{
		OnCharacterDeath();
	}
}

void ACppSideScrollerCharacter::Heal_Implementation(float healValue)
{
	healValue = FMath::Abs(healValue);
	if (healValue > 0.0F)
	{
		ModifyHealth(healValue);
	}	
}

void ACppSideScrollerCharacter::Damage_Implementation(float damageValue)
{
	damageValue = FMath::Abs(damageValue) * -1.0F;
	if (damageValue < 0.0F)
	{
		ModifyHealth(damageValue);
	}	
}

void ACppSideScrollerCharacter::OnCharacterDeath_Implementation()
{
	GetController()->SetIgnoreMoveInput(true);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetCharacterMovement()->SetJumpAllowed(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->GravityScale = 0.0F;
}

void ACppSideScrollerCharacter::ResetCharacter_Implementation()
{
	AController* controller = GetController();
	controller->UnPossess();
	this->Destroy();
	GetWorld()->GetAuthGameMode()->RestartPlayer(controller);
}

void ACppSideScrollerCharacter::MoveRight(float Value)
{
	// add movement in that direction
	FVector movementVector = FVector(0.f, -1.f, 0.f);
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ACppSideScrollerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACppSideScrollerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACppSideScrollerCharacter::MoveRight);

	ACppSideScrollerGameState* gameState = Cast<ACppSideScrollerGameState>(UGameplayStatics::GetGameState(this));
	if (gameState != nullptr)
	{
		PlayerInputComponent->BindAction("Restart", IE_Pressed, gameState, &ACppSideScrollerGameState::ResetGame);
	}	
}

void ACppSideScrollerCharacter::Jump()
{
	if (JumpCurrentCount < JumpMaxCount)
	{
		fallingDistance = 0.0F;
	}
	Super::Jump();
}


void ACppSideScrollerCharacter::Falling()
{
	Super::Falling();
}

void ACppSideScrollerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (fallingDistance > MinFallDamageHeight)
	{
		float fallDamage = (fallingDistance - MinFallDamageHeight) * FallDamageMultiplier;
		Damage(fallDamage);
	}
	fallingDistance = 0.0F;
}

void ACppSideScrollerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	previousLocation = GetActorLocation();
	ACppSideScrollerGameMode* gameMode = Cast<ACppSideScrollerGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->CurrentPlayerCharacter = this;
	}
}

void ACppSideScrollerCharacter::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (GetCharacterMovement()->IsFalling())
	{
		fallingDistance += FMath::Abs(GetActorLocation().Z - previousLocation.Z);
	}

	previousLocation = GetActorLocation();
}

#pragma optimize("", on)