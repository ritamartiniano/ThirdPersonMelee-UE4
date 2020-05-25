// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskFollowPlayer.generated.h"

UCLASS()
class THIRDPERSONMEELE_API UMyBTTaskFollowPlayer : public UBTTaskNode
{
	GENERATED_BODY()

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//declare this otherwise the code won't compile
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	
};
