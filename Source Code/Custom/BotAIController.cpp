// Fill out your copyright notice in the Description page of Project Settings.

#include "Custom.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "BotCharacter.h"
#include "BotAIController.h"

static FName NAME_ShouldWanderKey("ShouldWander");
static FName NAME_EnemyKey("Enemy");

ABotAIController::ABotAIController()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");

}

void ABotAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotAIController::OnSeePawn);

	if (BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);

		BlackboardComp->SetValueAsBool(NAME_ShouldWanderKey, true);

	}

}

void ABotAIController::OnSeePawn(APawn* SensedPawn)
{

	if (BlackboardComp && SensedPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("i see you"));

		BlackboardComp->SetValueAsBool(NAME_ShouldWanderKey, false);
		BlackboardComp->SetValueAsObject(NAME_EnemyKey, SensedPawn);
	}

}
