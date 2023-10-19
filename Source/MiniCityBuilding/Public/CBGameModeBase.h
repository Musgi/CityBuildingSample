// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/MCBAISpawner.h"
#include "GameFramework/GameModeBase.h"
#include "CBGameModeBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestinationMidPointChangedSignature, FVector3d, DestinationMidPoint);

UCLASS()
class MINICITYBUILDING_API ACBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> ActiveBuildings;
	FOnDestinationMidPointChangedSignature OnDestinationMidPointChanged;
	FVector3d MidPointBetweenBuldings;
	void GetMidPointBetweenBuildings();

	void ListenToBuildingEvents();
	UFUNCTION()
	void AddNewBuilding(AActor * NewBuilding);
	UFUNCTION()
	void RemvoeBuilding(AActor* OldBuilding);
	UFUNCTION()
	void RecalculateMidPoint(AActor* MovedBuilding);

	void SetActorInactivePool(AActor* Actor);
	
protected:
	UPROPERTY()
	TObjectPtr<AMCBAISpawner> AISpawaner;
	virtual void BeginPlay() override;
	
	
private:
	void ClearDebugDrawing();
};
