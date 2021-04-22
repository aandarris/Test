// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components\BoxComponent.h"
#include "GameFramework\PlayerState.h"
#include "CppSideScrollerCharacter.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ModifierTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ModifierTrigger"));
	ModifierTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	RootComponent = ModifierTrigger;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	ACppSideScrollerCharacter* character = Cast<ACppSideScrollerCharacter>(otherActor);
	if (character)
	{
		int newScore = character->GetPlayerState()->GetScore() + ScoreValue;
		character->GetPlayerState()->SetScore(newScore);
		OnCollect();
	}
}