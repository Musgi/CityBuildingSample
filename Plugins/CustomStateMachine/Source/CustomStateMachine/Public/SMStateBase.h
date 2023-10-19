// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMStateBase.generated.h"

/**
 * 
 */

UCLASS()
class CUSTOMSTATEMACHINE_API USMStateBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	bool bCanTick;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	bool bCanRepeat;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FName StateName;

	UPROPERTY(EditDefaultsOnly)
	TArray<USMStateBase*> CanSwitchToTheseStates;
	
	
	virtual void OnEnterState(AActor* StateOwner);
	virtual void TickState();
	virtual void OnExitState(AActor* StateOwner);
};
