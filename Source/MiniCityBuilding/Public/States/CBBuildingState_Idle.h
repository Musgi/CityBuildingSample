// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBBuildingBaseState.h"
#include "CBBuildingState_Idle.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UCBBuildingState_Idle : public UCBBuildingBaseState
{
	GENERATED_BODY()
public:
	UCBBuildingState_Idle();

	virtual void OnEnterState(AActor* StateOwner) override;
};
