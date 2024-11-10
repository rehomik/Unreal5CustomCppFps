// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemFunctionJumpComponent.generated.h"

class UInputAction;
class AEngineDic1CppCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENGINEDIC1CPP_API UItemFunctionJumpComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	UInputAction* JumpAction;

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	AEngineDic1CppCharacter* TargetCharacter;

public:	
	// Sets default values for this component's properties
	UItemFunctionJumpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
