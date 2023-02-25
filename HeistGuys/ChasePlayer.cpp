// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "GuardBBKeys.h"
#include "GuardAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerTree, uint8* NodeMemory)
{
	//Get TargetLocation via AI Controller
	AGuardAIController* const Controller = Cast<AGuardAIController>(OwnerTree.GetAIOwner());
	FVector const PlayerLocation = Controller->GetBlackboard()->GetValueAsVector(GuardBBKeys::TargetLocation);

	//Move to players current location
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

	//Finish Task
	FinishLatentTask(OwnerTree, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
