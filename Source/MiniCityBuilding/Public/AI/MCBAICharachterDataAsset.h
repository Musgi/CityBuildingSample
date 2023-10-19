// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MCBAICharachterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UMCBAICharachterDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMesh> CharachterMesh;
};
