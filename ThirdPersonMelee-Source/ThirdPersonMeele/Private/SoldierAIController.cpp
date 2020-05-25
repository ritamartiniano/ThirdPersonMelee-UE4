// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Monster.h"
#include "SoldierTargetPoint.h"

ASoldierAIController::ASoldierAIController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	soldierBehaviourTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("Soldier_BT"));
	soldierBlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BossBlackboard"));

	LocationToGoKey = "LocationToGo";
}

void ASoldierAIController::OnPossess(APawn * InPawn)
{
   Super::OnPossess(InPawn);
   AMonster* Monster = Cast<AMonster>(InPawn);

	if (Monster)
	{
		if (Monster->BehaviorTree->BlackboardAsset)
		{
			soldierBlackboardComp->InitializeBlackboard(*Monster->BehaviorTree->BlackboardAsset);

		}
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldierTargetPoint::StaticClass(), soldierTargetPoints);
		soldierBehaviourTreeComp->StartTree(*Monster->BehaviorTree);
	}
}

void ASoldierAIController::OnUnPossess()
{
	Super::OnUnPossess();
	soldierBehaviourTreeComp->StopTree();
}
void ASoldierAIController::StartFollowingPlayer()
{
	AActor *player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector playerPos = player->GetActorLocation();
	MoveToLocation(playerPos);
	//UE_LOG(LogTemp, Warning, TEXT("Soldier Controller not null"))
}

void ASoldierAIController::StartAttackingPlayer()
{
	AMonster* monster = Cast<AMonster>(GetPawn());
	AActor *player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	monster->Attack(player);
}

void ASoldierAIController::SetAttackRange(bool val)
{
	if (val)
	{
		isPatrolling = false;
	}
	soldierBlackboardComp->SetValueAsBool("isInAttackRange", val);
}

void ASoldierAIController::SetFollowRange(bool val)
{  if(val)
    {
	isPatrolling = false;
    }
	soldierBlackboardComp->SetValueAsBool("isInFollowRange", val);
}
