// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBluecube.h"

AGameModeBluecube::AGameModeBluecube(): TargetCount(0)
{
}

AGameModeBluecube::~AGameModeBluecube()
{
}

void AGameModeBluecube::DecrementTargetCount(int value)
{
	TargetCount -= value;
	if (TargetCount <= 0)
	{
		OnGameClear.Broadcast();
	}
}
