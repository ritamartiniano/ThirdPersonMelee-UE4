// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include "ThirdPersonMeele/ThirdPersonMeeleCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "SoldierAIController.h"
#include "Engine/Engine.h"

// Sets default values
AMonster::AMonster(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 600;
	HitPoints = 20;
	experience = 0;
	BPLoot = NULL;
	BaseAttackDamage = 20;
	AttackRestingTime = 1.5f;
	TimeSinceLastStrike = 0;
	Stamina = 100;
	distanceFromPlayer = 100;
	SightSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	AttackRangeSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

void AMonster::SetRestingState()
{

}

void AMonster::DestroyWeapon()
{
	MonsterWeapon->Destroy();
}

void AMonster::Attack(AActor * actor)
{
	if (isAttacking != true)
	{
		isAttacking = true;
		if (MonsterWeapon)
		{
			MonsterWeapon->Swing();
		}
	}
}

void AMonster::PostInitializeComponents()
{   
	Super::PostInitializeComponents();
	if (BP_MonsterSword)
	{
		MonsterWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BP_MonsterSword, FVector(), FRotator());

		if (MonsterWeapon)
		{
			const USkeletalMeshSocket *monsterSocket = GetMesh()->GetSocketByName(FName("WeaponHoldSocket"));
			monsterSocket->AttachActor(MonsterWeapon, GetMesh());
			MonsterWeapon -> monsterHolder = this;
			//temporarily, the weapon's attack damage can be the same as the owner's 
			MonsterWeapon-> AttackDamage = BaseAttackDamage;
		}
	}
	
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	AThirdPersonMeeleCharacter *player = Cast<AThirdPersonMeeleCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!player)
		return;
	
	FVector toPlayer = player->GetActorLocation() - GetActorLocation();
	float distancetoPlayer = toPlayer.Size();
	AMonsterAIController* AIcontroller = Cast<AMonsterAIController>(GetController());
	ASoldierAIController* SoldierAI = Cast<ASoldierAIController>(GetController());
	//if the player is not in the sightsphere of the monster
	if (distancetoPlayer > SightSphere->GetScaledSphereRadius())
	{
		if (AIcontroller != nullptr)
		{
			AIcontroller->SetAttackRange(false);
			AIcontroller->SetFollowRange(false);
		}
		if (SoldierAI != nullptr)
		{   
			SoldierAI->SetAttackRange(false);
			SoldierAI->SetFollowRange(false);
		}
		return;
	}
	toPlayer.Normalize();
	
	//move the monster towards the player
	//for the addmovement input to work, a controller under AI Controller should be selected

	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0;
	RootComponent->SetWorldRotation(toPlayerRotation);
	
	if (Stamina <= 45.0f)
	{
		AIcontroller->SetStartResting(true);
		AIcontroller->SetAttackRange(false);
		AIcontroller->SetFollowRange(false);
	}
	if (isInAttackRange(distancetoPlayer))
	{
		if (AIcontroller != nullptr)
		{
			AIcontroller->SetAttackRange(true);
			if (!TimeSinceLastStrike)
			{
				Attack(player);
				Stamina -= 0.5f;
				FString ss = FString::SanitizeFloat(Stamina);
				GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, ss);
			    
			}
			TimeSinceLastStrike += DeltaTime;
			if (TimeSinceLastStrike > AttackRestingTime)
			{
				TimeSinceLastStrike = 0;
			}
			return;
		}
		if (SoldierAI != nullptr)
		{
			SoldierAI->SetAttackRange(true);
			if (!TimeSinceLastStrike)
			{
				Attack(player);
			}
		}
	}
	else
	{
		AddMovementInput(toPlayer, Speed* DeltaTime);
		if (AIcontroller != nullptr)
		{
			    isAttacking = false;
				AIcontroller->SetAttackRange(false);
				AIcontroller->SetFollowRange(true);
		}
		if (SoldierAI != nullptr)
		{
			isAttacking = false; 
			SoldierAI->SetAttackRange(false);
			SoldierAI->SetFollowRange(true);
		}
	}

}

void AMonster::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{

}

