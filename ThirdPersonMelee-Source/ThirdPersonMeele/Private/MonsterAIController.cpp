// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster.h"

AMonsterAIController::AMonsterAIController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviourTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("Boss_BT"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BossBlackboard"));
}


void AMonsterAIController::OnPossess(class APawn * InPawn)
{
	Super::OnPossess(InPawn);

   AMonster* Monster = Cast<AMonster>(InPawn);

 if (Monster)
	{
		if (Monster->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Monster->BehaviorTree->BlackboardAsset);

		}
		BehaviourTreeComp->StartTree(*Monster->BehaviorTree);
	}
	
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
	BehaviourTreeComp->StopTree();
}

void AMonsterAIController::StartFollowingPlayer()
{
	AActor *player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector playerPos = player->GetActorLocation();
	MoveToLocation(playerPos);
}

void AMonsterAIController::StartAttackingPlayer()
{
	AMonster* monster = Cast<AMonster>(GetPawn());
	AActor *player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	monster->Attack(player);
	
}

void AMonsterAIController::StartResting()
{
	AMonster* monster = Cast<AMonster>(GetPawn());
	monster->SetRestingState();
}

void AMonsterAIController::SetFollowRange(bool val)
{
	BlackboardComp->SetValueAsBool("isInFollowRange", val);
}

void AMonsterAIController::SetAttackRange(bool val)
{
	BlackboardComp->SetValueAsBool("isInAttackRange", val);
}

void AMonsterAIController::SetStartResting(bool val)
{
	BlackboardComp->SetValueAsBool("isResting", val);
}

