// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Coin.h"
#include "HealthModifier.h"

#include "CppSideScrollerGameState.generated.h"

/**
 * 
 */
UCLASS()
class CPPSIDESCROLLER_API ACppSideScrollerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = GameState)
	TArray<ACoin*> Coins;

	UPROPERTY(BlueprintReadWrite, Category = GameState)
	TArray<AHealthModifier*> HealthModifiers;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = GameState)
	void ResetGame();
	virtual void ResetGame_Implementation();
};
