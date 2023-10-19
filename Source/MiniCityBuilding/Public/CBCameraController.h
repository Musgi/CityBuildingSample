// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBCameraCharachter.h"
#include "GameFramework/PlayerController.h"
#include "CBCameraController.generated.h"

/**
 * 
 */
UCLASS()
class MINICITYBUILDING_API ACBCameraController : public APlayerController
{
	GENERATED_BODY()

public:
	FToggleInfoMenu OnToggleMenuInfo;
	
protected:
	UPROPERTY()
	ACBCameraCharachter* MyCameraCharachter;
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float ZoomSpeed;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float MaxZoom;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float MinZoom;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float MinPitch;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float MaxPitch;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float LookingRotationSpeed;
	UPROPERTY(EditDefaultsOnly, Category= "CustomInput")
	float BuildingRotationSpeed;
	
	
	bool bIsRightMouseClicked;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void RightMouseClick();
	void RightMouseRelease();
	void LeftMouseClick();
	void LeftMouseRelease();
	void CameraZoomController(float Direction);
	void MoveForwardOrBackward(float Direction);
	void MoveLeftOrRight(float Direction);
	void LookLeftOrRight(float Direction);
	void LookUpOrDown(float Direction);
	void RotateBuilding(float Direction);
	void SellBuilding();
	void ToggleSnap();
	void ToggleInfo();
	void DisableBuildingContainer();
	bool IsMouseOverUI();
};
