// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBBuildingDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UCBBuildingDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName BuildingName;

	UPROPERTY(EditDefaultsOnly)
	FString Details;
	
	UPROPERTY(EditDefaultsOnly)
	int32 Cost;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh*  StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> BuildingIcon;

	UPROPERTY(EditDefaultsOnly)
	int32 MaterialCount;
	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> FadeMaterials;
	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> DefaultMaterials;
};
