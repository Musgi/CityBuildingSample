// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBBuildingBaseState.h"
#include "CBBuildingState_Selected.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UCBBuildingState_Selected : public UCBBuildingBaseState
{
	GENERATED_BODY()
public:
	UCBBuildingState_Selected();

	void OnEnterState(AActor* StateOwner) override;
	void TickState() override;
	void OnExitState(AActor* StateOwner) override;
};
