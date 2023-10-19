// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CBFakeBorderButton.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UCBFakeBorderButton : public UButton
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DisableEvents();
	
};