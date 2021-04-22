// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class CPPSIDESCROLLER_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ModifierTrigger;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coin)
	int ScoreValue;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Coin)
	void OnCollect();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Coin)
	void Reset();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult);
};
