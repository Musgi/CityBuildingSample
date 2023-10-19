// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBBuildingButton.h"
#include "Components/ActorComponent.h"
#include "CBUIControllerComponent.generated.h"

class ACBCameraCharachter;
class UCBMainHud;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINICITYBUILDING_API UCBUIControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCBUIControllerComponent();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCBMainHud> MainHudClass;
	UPROPERTY()
	UCBMainHud* MainHud;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MyMoneyClass;
	UPROPERTY()
	UUserWidget* MyMoney;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCBBuildingButton> BuildingButtonClass;
	UPROPERTY()
	UCBBuildingButton* BuildingButton;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCBBuildingDataAsset*> BuildingData;

protected:
	// Called when the game starts
	
	UPROPERTY()
	ACBCameraCharachter * MyCharachter;
	virtual void BeginPlay() override;

public:
	
	void UpdateMoneyUI(int CurrentMoney);

	void ListenToButtonEvents(UCBBuildingButton* BuildingButton);

	void ToggleInputInfo();
	UFUNCTION()
	void ButtonClicked(UCBBuildingDataAsset* FuncBuildingData);
	UFUNCTION()
	void ButtonHovered(int Cost, FName Name);
	UFUNCTION()
	void ButtonUnHovered();
	UFUNCTION()
	void EnableBuildingsContainer();
	UFUNCTION()
	void DisableBuildingsContainer();
};
