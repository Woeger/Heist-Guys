// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "GuardAIController.h"
#include "GuardBBKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerTree, uint8* NodeMemory)
{
	//Get AIController + Assigned Pawn
	auto const Controller = Cast<AGuardAIController>(OwnerTree.GetAIOwner());
	auto const Guard = Controller->GetPawn();

	//Get Starting Location
	FVector const StartingLocation = Guard->GetActorLocation();

	//Generate Random Location from NavMesh
	FNavLocation RandomLocation;
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (NavigationSystem->GetRandomPointInNavigableRadius(StartingLocation, SearchRadius, RandomLocation, nullptr))
	{
		Controller->GetBlackboard()->SetValueAsVector(GuardBBKeys::TargetLocation, RandomLocation.Location);
	}

	//Finish Task
	FinishLatentTask(OwnerTree, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
