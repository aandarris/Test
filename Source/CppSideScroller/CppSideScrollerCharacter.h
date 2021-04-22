// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CppSideScrollerCharacter.generated.h"

UCLASS(config=Game)
class ACppSideScrollerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FallDamage)
	float MinFallDamageHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FallDamage)
	float FallDamageMultiplier;

	UFUNCTION(BlueprintCallable, Category = Health)
	bool IsCharacterAlive() const { return CurrentHealth > 0.0F; }

	UFUNCTION(BlueprintCallable, Category = Health)
	void ModifyHealth(float healthModification);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Health)
	void Heal(float healValue);
	virtual void Heal_Implementation(float healValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Health)
	void Damage(float damageValue);
	virtual void Damage_Implementation(float damageValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Reset)
	void ResetCharacter();
	virtual void ResetCharacter_Implementation();

protected:	

	UFUNCTION(BlueprintNativeEvent, Category = Health)
	void OnCharacterDeath();
	virtual void OnCharacterDeath_Implementation();	

	/** Called for side to side input */
	void MoveRight(float Val);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:

	virtual void Jump() override;
	virtual void Falling() override;
	virtual void Landed(const FHitResult& Hit) override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	ACppSideScrollerCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }	

private:
	FVector previousLocation;
	float fallingDistance;
};
