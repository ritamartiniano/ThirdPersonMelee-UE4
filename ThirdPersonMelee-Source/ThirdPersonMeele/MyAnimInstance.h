// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONMEELE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* MeleeAttackMontage;

		/*Holds a reference to the character's movement speed*/
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MovementSpeed;

		/*Updates the Movement Speed variable*/
		UFUNCTION(BlueprintCallable, Category = "AnimationUpdates")
		void UpdateMovementSpeed();

		/*True if the character can perform a second attack*/
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bAcceptsSecondAttackInput;

		/*Ture if the character can perform a third attack*/
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bAcceptsThirdAttackInput;

		UFUNCTION(BlueprintCallable, Category = "AnimationUpdates")
		bool isMontagePlaying(UAnimMontage* meeleAttack);

public: 
	/*Determines which attack animation will be played*/
	void Attack();
	
};
