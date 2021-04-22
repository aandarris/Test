// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CppSideScrollerGameMode.generated.h"

UCLASS(minimalapi)
class ACppSideScrollerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACppSideScrollerGameMode();

	UPROPERTY(BlueprintReadOnly, Category = Player)
	class ACppSideScrollerCharacter* CurrentPlayerCharacter;
};