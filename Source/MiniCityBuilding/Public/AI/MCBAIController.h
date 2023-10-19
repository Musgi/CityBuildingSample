// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MCBAIController.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API AMCBAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMCBAIController();
	
protected:
	UPROPERTY(EditAnywhere, Category= "AI")
	TObjectPtr<UBehaviorTree> MainBhevaiourTree;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void UpdateBlackBoardDestinationValue(FVector3d NewLocation);
};
