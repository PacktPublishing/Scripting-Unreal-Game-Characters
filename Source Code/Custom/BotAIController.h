// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BotAIController.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOM_API ABotAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	ABotAIController();

	virtual void Possess(APawn* InPawn) override;
	
protected:

	UPROPERTY(EditDefaultsOnly)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditDefaultsOnly)
	class UBlackboardComponent* BlackboardComp;

	UFUNCTION()
	void OnSeePawn(class APawn* SensedPawn);

public:

	FORCEINLINE class UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

};
