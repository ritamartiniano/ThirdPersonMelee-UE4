// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

UCLASS()
class THIRDPERSONMEELE_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public: 

	AMonsterAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(class APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

	UBehaviorTreeComponent* BehaviourTreeComp;

	UBlackboardComponent* BlackboardComp;

	void StartFollowingPlayer();

	void StartAttackingPlayer();

	void StartResting();

	//to set the blackboard values
	void SetFollowRange(bool val);

	void SetAttackRange(bool val);

	void SetStartResting(bool val);

};
