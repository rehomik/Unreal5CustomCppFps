// Fill out your copyright notice in the Description page of Project Settings.


#include "HudGameModeBluecube.h"
#include "Blueprint/UserWidget.h"

void AHudGameModeBluecube::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClassMain)
	{
		WidgetMain = CreateWidget<UUserWidget>(GetWorld(), WidgetClassMain);
		if (WidgetMain)
		{
			WidgetMain->AddToViewport();
		}
	}

	if (WidgetClassTimer)
	{
		WidgetTimer = CreateWidget<UUserWidget>(GetWorld(), WidgetClassTimer);
		if (WidgetTimer)
		{
			WidgetTimer->AddToViewport();
		}
	}
}
