// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFunctionJumpComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EngineDic1CppCharacter.h"
#include "TimerManager.h"
#include <EnhancedInputSubsystems.h>

// Sets default values for this component's properties
UItemFunctionJumpComponent::UItemFunctionJumpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemFunctionJumpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(TargetCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(AdditionalMovement, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Jumping
			FEnhancedInputActionEventBinding& jumpAction = EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, TargetCharacter, &ACharacter::Jump);
			this->JumpActionHandle = jumpAction.GetHandle();

			FEnhancedInputActionEventBinding& endJumpAction = EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, TargetCharacter, &ACharacter::StopJumping);
			this->EndJumpActionHandle = endJumpAction.GetHandle();
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UItemFunctionJumpComponent::DestroyItemFunction, 5.0f, false);
}

void UItemFunctionJumpComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(TargetCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->RemoveMappingContext(AdditionalMovement);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
 			EnhancedInputComponent->RemoveActionBindingForHandle(this->JumpActionHandle);
			EnhancedInputComponent->RemoveActionBindingForHandle(this->EndJumpActionHandle);
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

// Called every frame
void UItemFunctionJumpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemFunctionJumpComponent::DestroyItemFunction()
{
	DestroyComponent();
}