// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class HEISTGUYS_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolPath();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> PatrolPoints;

//Getters/Setters
public:
	FORCEINLINE FVector GetPatrolPoint(int const index) { return PatrolPoints[index]; }
	FORCEINLINE int GetPatrolLength() { return PatrolPoints.Num(); }
};
