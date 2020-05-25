// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskFollowPlayer.h"
#include "MonsterAIController.h"
#include "SoldierAIController.h"

EBTNodeResult::Type UMyBTTaskFollowPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	ASoldierAIController* SoldierController = Cast<ASoldierAIController>(OwnerComp.GetAIOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
		UE_LOG(LogTemp, Warning, TEXT("Boss Controller null"));
	}
	else if (Controller != nullptr)
	{
		Controller->StartFollowingPlayer();
		UE_LOG(LogTemp, Warning, TEXT("Boss Controller not null"));
		return EBTNodeResult::Succeeded;
	}
    if (SoldierController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Soldier Controller not null"));
		SoldierController->StartFollowingPlayer();
		return EBTNodeResult::Succeeded;
	}
	else if (SoldierController == nullptr)
	{
		return EBTNodeResult::Failed;
		UE_LOG(LogTemp, Warning, TEXT("Soldier Controller null"));
	}
	return EBTNodeResult::Failed;
}
