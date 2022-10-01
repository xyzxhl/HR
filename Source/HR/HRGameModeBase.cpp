// Copyright Epic Games, Inc. All Rights Reserved.


#include "HRGameModeBase.h"

AHRGameModeBase::AHRGameModeBase()
{
    // set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/HRCharacter/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

