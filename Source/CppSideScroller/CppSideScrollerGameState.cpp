// Fill out your copyright notice in the Description page of Project Settings.

#include "CppSideScrollerGameState.h"
#include "Gameframework/PlayerState.h"
#include "CppSideScrollerCharacter.h"

void ACppSideScrollerGameState::ResetGame_Implementation()
{
	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		PlayerArray[i]->Score = 0;
		ACppSideScrollerCharacter* character = Cast<ACppSideScrollerCharacter>(PlayerArray[i]->GetPawn());
		if (character != nullptr)
		{
			character->ResetCharacter();
		}
	}

	for (int i = 0; i < Coins.Num(); i++)
	{
		if (Coins[i] != nullptr)
		{
			Coins[i]->Reset();
		}
	}

	for (int i = 0; i < HealthModifiers.Num(); i++)
	{
		if (HealthModifiers[i] != nullptr)
		{
			HealthModifiers[i]->Reset();
		}
	}
}