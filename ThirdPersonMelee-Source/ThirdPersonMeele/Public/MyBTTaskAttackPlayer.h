// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskAttackPlayer.generated.h"

UCLASS()
class THIRDPERSONMEELE_API UMyBTTaskAttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	    
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	
};
