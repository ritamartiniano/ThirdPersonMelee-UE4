	// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior_HealthComponent.h"
#include "..\Public\Warrior_HealthComponent.h"

// Sets default values for this component's properties
UWarrior_HealthComponent::UWarrior_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealth = 100;
	Health = DefaultHealth;
}


// Called when the game starts
void UWarrior_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UWarrior_HealthComponent::TakeDamage);
	}
}

void UWarrior_HealthComponent::TakeDamage(AActor * DamageActor, float Damage, const UDamageType * damageType, AController * InstigatedBy, AActor * damageCauser)
{   
	if (Damage <= 0)
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
}


