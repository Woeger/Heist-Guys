// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GuardAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;

UCLASS()
class HEISTGUYS_API AGuardAIController : public AAIController
{
	GENERATED_BODY()

public:
	AGuardAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* PossessedPawn) override;
	UFUNCTION()
	void OnTargetDetected(AActor* DetectedActor, FAIStimulus const AIStimulus);

private:
	//Sensing
	UFUNCTION()
	void OnUpdated(TArray<AActor*> const& UpdatedActors);
	void SetupPerceptionSystem();
	UAISenseConfig_Sight* SightConfig;

	//Behavior Trees
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComponent;




//Getters/Setters
public:
	FORCEINLINE UBlackboardComponent* GetBlackboard() { return BlackboardComponent; }
	
};
