// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudGameModeBluecube.generated.h"

/**
 * 
 */
UCLASS()
class ENGINEDIC1CPP_API AHudGameModeBluecube : public AHUD
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> WidgetClassMain;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> WidgetClassTimer;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UUserWidget* WidgetMain;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UUserWidget* WidgetTimer;
};
