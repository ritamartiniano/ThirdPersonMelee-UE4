// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Monster.h"
#include "MeleeWeapon.generated.h"

class AThirdPersonMeeleCharacter;

UCLASS()
class THIRDPERSONMEELE_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon(const FObjectInitializer& ObjectInitializer);

	// The amount of damage attacks by this weapon do
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
	float AttackDamage;

	// A list of things the melee weapon already hit this swing
	// Ensures each thing sword passes thru only gets hit once
	TArray<AActor*> ThingsHit;

	// prevents damage from occurring in frames where
    // the sword is not swinging
	bool Swinging;

	AThirdPersonMeeleCharacter* PlayerHolder;

	class AMonster* monsterHolder = nullptr;

	//bouding box that determines when melee weapon hit 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UBoxComponent* ProxBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	void Swing();
	void Rest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
