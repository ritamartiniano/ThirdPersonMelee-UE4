// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskAttackPlayer.h"
#include "MonsterAIController.h"

EBTNodeResult::Type UMyBTTaskAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Controller->StartAttackingPlayer();
	return EBTNodeResult::Succeeded;
}
