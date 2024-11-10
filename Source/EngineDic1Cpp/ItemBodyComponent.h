// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ItemBodyComponent.generated.h"

class UInputAction;

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class ENGINEDIC1CPP_API UItemBodyComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
};
