// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthModifier.generated.h"

UENUM()
enum class EHealthModificationType : uint8
{
	HMT_Heal	UMETA(DisplayName = "Heal"),
	HMT_Damage	UMETA(DisplayName = "Damage"),
};

UCLASS()
class CPPSIDESCROLLER_API AHealthModifier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthModifier();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ModifierTrigger;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HealthModifier)
	EHealthModificationType HealthModificationType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HealthModifier)
	float HealthModificationValue;	

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = HealthModifier)
	void OnHeal();

	UFUNCTION(BlueprintImplementableEvent, Category = HealthModifier)
	void OnDamage();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = HealthModifier)
	void Reset();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult);
};
