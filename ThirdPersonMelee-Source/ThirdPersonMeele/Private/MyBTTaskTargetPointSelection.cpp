// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskTargetPointSelection.h"
#include "SoldierAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SoldierTargetPoint.h"

EBTNodeResult::Type UMyBTTaskTargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ASoldierAIController* AIController = Cast<ASoldierAIController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
		ASoldierTargetPoint* currentPoint = Cast<ASoldierTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
	    
		TArray<AActor*> AvailableTargetPoints = AIController->GetAvailableTargetPoints();
	
		int32 RandomIndex;

		ASoldierTargetPoint* NextTargetPoint = nullptr;

		do {
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			NextTargetPoint = Cast<ASoldierTargetPoint>(AvailableTargetPoints[RandomIndex]);
		
		} while (currentPoint == NextTargetPoint);

		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
		
		AIController->isPatrolling = true;

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
