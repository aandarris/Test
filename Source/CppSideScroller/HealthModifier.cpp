// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthModifier.h"
#include "Components\BoxComponent.h"
#include "CppSideScrollerCharacter.h"

// Sets default values
AHealthModifier::AHealthModifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ModifierTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ModifierTrigger"));
	ModifierTrigger->OnComponentBeginOverlap.AddDynamic(this, &AHealthModifier::OnOverlapBegin);
	RootComponent = ModifierTrigger;

	HealthModificationType = EHealthModificationType::HMT_Heal;
	HealthModificationValue = 1.0F;
}

void AHealthModifier::BeginPlay()
{
	Super::BeginPlay();	
}

void AHealthModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthModifier::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	ACppSideScrollerCharacter* character = Cast<ACppSideScrollerCharacter>(otherActor);
	if (character)
	{
		switch (HealthModificationType)
		{
		case EHealthModificationType::HMT_Heal:
			character->Heal(HealthModificationValue);
			OnHeal();
			break;
		case EHealthModificationType::HMT_Damage:
			character->Damage(HealthModificationValue);
			OnDamage();
			break;
		}
	}
}