// Fill out your copyright notice in the Description page of Project Settings.

#include "Custom.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIWanderPoint.h"
#include "BotAIController.h"
#include "Task_FindWanderPoint.h"

static FName NAME_WanderPointKey("WanderPoint");

EBTNodeResult::Type UTask_FindWanderPoint::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ABotAIController* AIController = Cast<ABotAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* AIBlackboard = AIController->GetBlackboardComp();

	if (!AIController || !AIBlackboard)
	{
		return EBTNodeResult::Failed;
	}

	TArray<AActor*> WanderPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIWanderPoint::StaticClass(), WanderPoints);

	if (WanderPoints.Num() == 0)
		return EBTNodeResult::Failed;

	AAIWanderPoint* CurrentWanderPoint = Cast<AAIWanderPoint>(AIBlackboard->GetValueAsObject(NAME_WanderPointKey));
	AAIWanderPoint* NewWanderPoint = Cast<AAIWanderPoint>(WanderPoints[FMath::RandRange(0, WanderPoints.Num() - 1)]);

	while (NewWanderPoint == CurrentWanderPoint)
	{
		NewWanderPoint = Cast<AAIWanderPoint>(WanderPoints[FMath::RandRange(0, WanderPoints.Num() - 1)]);
	}

	AIBlackboard->SetValueAsObject(NAME_WanderPointKey, NewWanderPoint);
	return EBTNodeResult::Succeeded;

}

