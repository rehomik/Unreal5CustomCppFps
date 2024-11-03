// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "EngineDic1CppCharacter.h"
#include "EngineDic1CppProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	setCurrentBulletCount(maxBulletCount);
}

void UTP_WeaponComponent::setCurrentBulletCount(int count)
{
	bulletCount = count;
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("bulletCount: " + FString::FromInt(bulletCount)));

	if (bulletCount <= 0)
	{
		return;
	}

	--bulletCount;

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AEngineDic1CppProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::Drop()
{
	OnWeaponDrop.Broadcast(Character);
}

void UTP_WeaponComponent::SwapWeapon(UTP_WeaponComponent* previousWeapon)
{
	if (Character == nullptr)
	{
		return;
	}

	OnWeaponSwap.Broadcast(previousWeapon, Character);
}

void UTP_WeaponComponent::Reload()
{
	if (Character == nullptr)
	{
		return;
	}

	OnWeaponReload.Broadcast(maxBulletCount);
}

bool UTP_WeaponComponent::AttachWeapon(AEngineDic1CppCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	UTP_WeaponComponent* weapon = nullptr;
	Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>(&weapon);

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr)
	{
		return false;
	}

	// �̹� ���� ���� ���Ⱑ �ִ� ��� ���� ó��.
	if (weapon != nullptr)
	{
		SwapWeapon(weapon);

		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);

	// ���� ���� ���� ����.
	SetSimulatePhysics(false);
	SetCollisionProfileName(TEXT("NoCollision"));

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);

			// Weapon Deop
			EnhancedInputComponent->BindAction(WeaponDropAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Drop);

			// Reload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Reload);
		}
	}

	return true;
}

bool UTP_WeaponComponent::DetachWeapon()
{
	if (Character == nullptr || !Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>())
	{
		return false;
	}

	// ������Ʈ ���Ϳ��� �и�.
	DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Character->RemoveInstanceComponent(this);

	// ���� ���� ���� �۵�.
	SetSimulatePhysics(true);
	SetCollisionProfileName(TEXT("PhysicsActor"));

	// ���� ���� ��ϵ� Ű ���ε� ����.
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
			Subsystem->RemoveMappingContext(FireMappingContext);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->ClearActionBindings();
		}
	}

	return true;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}