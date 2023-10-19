// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBFakeBorderButton.h"
#include "Blueprint/UserWidget.h"
#include "CBMainHud.generated.h"

class UHorizontalBox;
class UBorder;
class UButton;
class UTextBlock;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API UCBMainHud : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> BuildingButtonContainer;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> BuildingInfoContainer;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BuildingInfo;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BuildingCost;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> InputControlInfoContainer;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> BuildingMenuToggle;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> BuildingContainerBorder;
	//UPROPERTY(meta=(BindWidget))
	//TObjectPtr<UCBFakeBorderButton> FakeBorderButton;
};
