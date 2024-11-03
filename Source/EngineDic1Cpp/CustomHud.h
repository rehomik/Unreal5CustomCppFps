// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHud.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ENGINEDIC1CPP_API ACustomHud : public AHUD
{
	GENERATED_BODY()

private :
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> WidgetClass;
};
