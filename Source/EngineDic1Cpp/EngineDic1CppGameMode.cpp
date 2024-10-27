// Copyright Epic Games, Inc. All Rights Reserved.

#include "EngineDic1CppGameMode.h"
#include "EngineDic1CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEngineDic1CppGameMode::AEngineDic1CppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
