// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ThirdPersonMeele/ThirdPersonMeeleCharacter.h"
#include "HealthPickUp.generated.h"


UCLASS()
class THIRDPERSONMEELE_API AHealthPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUp(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = HealthProperties)
	UBoxComponent* box;

	UFUNCTION()
	void onOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = HealthProperties)
	float health;

	AThirdPersonMeeleCharacter* player;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
