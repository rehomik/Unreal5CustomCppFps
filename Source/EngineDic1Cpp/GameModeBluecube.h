// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBluecube.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameClear);

/**
 * 
 */
UCLASS()
class ENGINEDIC1CPP_API AGameModeBluecube : public AGameModeBase
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere, Category = "Game")
	int TargetCount;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnGameClear OnGameClear;

public :
	AGameModeBluecube();
	~AGameModeBluecube();

	UFUNCTION(BlueprintCallable)
	void DecrementTargetCount(int value);
};
