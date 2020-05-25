// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "MeleeWeapon.h"
#include "Monster.generated.h"
class ThirdPersonMeeleCharacter;

UCLASS()
class THIRDPERSONMEELE_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPLoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float AttackRestingTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float TimeSinceLastStrike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Stamina;

	//Range for monster's sight
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;

	//Range for attack.Visualizes as a sphere in the editor
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* AttackRangeSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties)
	UClass* BP_MonsterSword;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
    class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterState)
	bool isAttacking;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterState)
	bool isResting;

	float distanceFromPlayer;

	// The MeleeWeapon instance (set if the character is using
	// a melee weapon)
	class AMeleeWeapon* MonsterWeapon;

	UFUNCTION(BlueprintCallable)
	void DestroyWeapon();

	void Attack(AActor* actor);
	
	void SetRestingState();

	inline bool isInSightRange(float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}

	inline bool isInAttackRange(float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
