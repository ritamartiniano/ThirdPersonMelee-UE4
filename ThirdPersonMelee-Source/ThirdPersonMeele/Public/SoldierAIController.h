// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "SoldierAIController.generated.h"


UCLASS()
class THIRDPERSONMEELE_API ASoldierAIController : public AAIController
{
	GENERATED_BODY()

public:

	ASoldierAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(class APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	UBehaviorTreeComponent* soldierBehaviourTreeComp;

	UBlackboardComponent* soldierBlackboardComp;

	TArray<AActor*> soldierTargetPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SoldierSpeed)
	bool isPatrolling = false;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const {
		return soldierBlackboardComp;
	}
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() {
		return soldierTargetPoints;
	}

	void StartFollowingPlayer();

	void StartAttackingPlayer();

	void SetFollowRange(bool val);

	void SetAttackRange(bool val);
	
};
