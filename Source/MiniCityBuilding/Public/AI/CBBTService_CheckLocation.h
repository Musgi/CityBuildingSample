// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBBTService_CheckLocation.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UCBBTService_CheckLocation : public UBTService
{
	GENERATED_BODY()

protected:
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
