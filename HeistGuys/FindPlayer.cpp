// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayer.h"
#include "GuardAIController.h"
#include "GuardBBKeys.h"
#include "GameFrameWork/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UFindPlayer::UFindPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerTree, uint8* NodeMemory)
{
	//Get controller of PlayerCharacter + Guard
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Controller = Cast<AGuardAIController>(OwnerTree.GetAIOwner());

	//Get location of player
	FVector const PlayerLocation = Player->GetActorLocation();

	//If we're searching, generate a random target near the player
	if (IsSearchingRandom)
	{
		FNavLocation RandomLocation;
		UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		if (NavigationSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, RandomLocation, nullptr))
		{
			Controller->GetBlackboard()->SetValueAsVector(GuardBBKeys::TargetLocation, RandomLocation.Location);
		}
	}

	//Otherwise set our target to the player location
	else
	{
		Controller->GetBlackboard()->SetValueAsVector(GuardBBKeys::TargetLocation, PlayerLocation);
	}

	//Finish Task
	FinishLatentTask(OwnerTree, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
