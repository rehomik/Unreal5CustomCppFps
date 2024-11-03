// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHud.h"
#include "Blueprint/UserWidget.h"

void ACustomHud::BeginPlay()
{
	Super::BeginPlay();

	// Create a new Widget
	if (WidgetClass)
	{
		// Create the widget and store it
		auto CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

		// Add it to the viewport
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
