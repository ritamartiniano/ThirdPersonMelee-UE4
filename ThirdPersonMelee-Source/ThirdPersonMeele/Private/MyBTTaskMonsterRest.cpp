// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskMonsterRest.h"
#include "MonsterAIController.h"

EBTNodeResult::Type UMyBTTaskMonsterRest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Controller->StartResting();
	return EBTNodeResult::Succeeded;
}