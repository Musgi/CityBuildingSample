// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBBuildingDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CBBuildingButton.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, UCBBuildingDataAsset*, BuildingData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonHovered, int, Cost, FName, Name);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUnHovered);

UCLASS()
class MINICITYBUILDING_API UCBBuildingButton : public UUserWidget
{
	GENERATED_BODY()
	//ref to data asset


public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button;
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	UPROPERTY()
	UCBBuildingDataAsset* BuildingData;


	FOnButtonClicked MyButtonClicked;
	FOnButtonHovered MyButtonHovered;
	FOnButtonUnHovered MyButtonUnHovered;


	UFUNCTION()
	void InializeButton(UCBBuildingDataAsset* BuildingDataInitialize);


	UFUNCTION()
	void OnButtonClicked();
	UFUNCTION()
	void OnButtonHovered();
	UFUNCTION()
	void OnButtonUnhovered();
};
