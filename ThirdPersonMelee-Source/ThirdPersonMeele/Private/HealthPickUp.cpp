// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"


// Sets default values
AHealthPickUp::AHealthPickUp(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	box = ObjectInitalizer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollision"));
	
	box->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::onOverlapBegin);
	
}

void AHealthPickUp::onOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (OtherActor == (AActor* )player)
	{
		UE_LOG(LogTemp, Warning, TEXT("isplayer"));
	}
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

