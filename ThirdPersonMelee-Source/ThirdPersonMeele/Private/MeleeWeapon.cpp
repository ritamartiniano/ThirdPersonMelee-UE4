// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Engine.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Swinging = false;
	
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));

	RootComponent = Mesh;
	ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	
	ProxBox -> OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::Prox);
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

int AMeleeWeapon::Prox_Implementation(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return -1;
	}
	// avoid hitting things while sword isn't swinging,
	// avoid hitting yourself
	// avoid hitting the same OtherActor twice
	if (Swinging && OtherActor != (AActor *) PlayerHolder && !ThingsHit.Contains(OtherActor))
	{   
		OtherActor->TakeDamage(AttackDamage, FDamageEvent(), NULL, this);
		ThingsHit.Add(OtherActor);
	}
	if (Swinging && OtherActor != (AActor *)monsterHolder && !ThingsHit.Contains(OtherActor))
	{   
		OtherActor->TakeDamage(AttackDamage, FDamageEvent(), NULL, this);
		ThingsHit.Add(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Damage Taken"));
	}
	
	return 0;
}

void AMeleeWeapon::Swing()
{
	ThingsHit.Empty(); //empty the list
	Swinging = true;
}

void AMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


