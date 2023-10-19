// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBBaseBuilding.h"
#include "CBInteractionComponent.h"
#include "CBUIControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomHeader.h"
#include "CBCameraCharachter.generated.h"


DECLARE_MULTICAST_DELEGATE(FToggleInfoMenu);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingCreatedSignature, AActor*, CreatedBuilding);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDestroyedSignature, AActor*, DestroyedBuilding);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingLocationChangedSignature, AActor*, TranslatedBuilding);

UCLASS()
class MINICITYBUILDING_API ACBCameraCharachter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACBCameraCharachter() ;
	void LeftMouseClick();
	void LeftMouseRelease();
	void RotateBuilding(float Direction, float RotationSpeed);
	void SellBuilding();
	virtual void Tick(float DeltaSeconds) override;
	bool SpawnBuilding(UCBBuildingDataAsset* BuildingData);
	void ToggleSnap();
	void ToggleInfoMenu();
	UFUNCTION(Exec)
	void AddMoney(int Value);


	FOnBuildingCreatedSignature OnBuildingCreated;
	FOnBuildingDestroyedSignature OnBuildingDestroyed;
	FOnBuildingLocationChangedSignature OnBuildingLocationChanged;
	
	UFUNCTION()
	void BuildingCreated();
	UFUNCTION()
	void BuildingDestroyed();
	UFUNCTION()
	void BuildingMoved();
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCBInteractionComponent> InteractionComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACBBaseBuilding> SpawnableBuilding;
	UPROPERTY(VisibleAnywhere)
	AActor* HoveredActor;
	UPROPERTY(VisibleAnywhere)
	AActor* SelectedActor;
	UPROPERTY(VisibleAnywhere)
	AActor* SpawningActor;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCBUIControllerComponent> UIManager;

	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	int32 SnappingGridCellSize;

	TEnumAsByte<EGameState> CurrentGameState;
	int32 CurrentMoney;
	FTransform SelectedActorOriginalTransform;
	FVector MouseDragOffset;
	float CurrentSpawningBuildingCost = 0;
	float SnappingCoolDown = .1f;
	bool bIsLeftMouseClicked;
	bool bSnappingActive = false;

	virtual void BeginPlay() override;
	void DragActor(AActor* TargetActor);
	AActor* LineTraceForBuildingSelectingAndOutline();
	void UpdateMoney();
	bool UpdateBuildingState(FString NewState, AActor* TargetActor);
	void HoveringnBuilding();
	void CalculateMouseDragOffset(AActor* TargetActor);
	FVector RoundToNearestGridCellLocation(FVector Location);
	FRotator RoundYAWToNearest90XRotation(FRotator Rotation);
};
