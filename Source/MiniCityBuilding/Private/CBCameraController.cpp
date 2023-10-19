// Fill out your copyright notice in the Description page of Project Settings.


#include "CBCameraController.h"

#include "CBMainHud.h"
#include "Components/Border.h"
#include "Components/Viewport.h"
#include "Kismet/GameplayStatics.h"

void ACBCameraController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	if (GetCharacter() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "none");
		return;
	}
	MyCameraCharachter = Cast<ACBCameraCharachter>(GetCharacter());
	CameraComponent = Cast<UCameraComponent>(MyCameraCharachter->GetComponentByClass(UCameraComponent::StaticClass()));
	SpringArmComponent = Cast<USpringArmComponent>(
		MyCameraCharachter->GetComponentByClass(USpringArmComponent::StaticClass()));
}

void ACBCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ACBCameraController::RightMouseClick);
	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ACBCameraController::RightMouseRelease);
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ACBCameraController::LeftMouseClick);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ACBCameraController::LeftMouseRelease);
	InputComponent->BindAxis("MoveForwardOrBackward", this, &ACBCameraController::MoveForwardOrBackward);
	InputComponent->BindAxis("MoveLeftOrRight", this, &ACBCameraController::MoveLeftOrRight);
	InputComponent->BindAxis("ZoomInOrOut", this, &ACBCameraController::CameraZoomController);
	InputComponent->BindAxis("LookUpOrDown", this, &ACBCameraController::LookUpOrDown);
	InputComponent->BindAxis("LookLeftOrRight", this, &ACBCameraController::LookLeftOrRight);
	InputComponent->BindAxis("Rotate", this, &ACBCameraController::RotateBuilding);
	// InputComponent->BindAction("EditMode", IE_Pressed, this, &ACBCameraController::EditMode);
	// InputComponent->BindAction("ObserveMode", IE_Pressed, this, &ACBCameraController::ObserveMode);
	InputComponent->BindAction("Sell", IE_Pressed, this, &ACBCameraController::SellBuilding);
	InputComponent->BindAction("Snap", IE_Pressed, this, &ACBCameraController::ToggleSnap);
	InputComponent->BindAction("ToggleInfo", IE_Pressed, this, &ACBCameraController::ToggleInfo);
}

void ACBCameraController::RightMouseClick()
{
	bIsRightMouseClicked = true;
}

void ACBCameraController::RightMouseRelease()
{
	bIsRightMouseClicked = false;
	//check if released over ui bta3t el buildings
	DisableBuildingContainer();
}

void ACBCameraController::LeftMouseClick()
{
	if (MyCameraCharachter == nullptr) return;
	MyCameraCharachter->LeftMouseClick();
}

void ACBCameraController::LeftMouseRelease()
{
	if (MyCameraCharachter == nullptr) return;
	MyCameraCharachter->LeftMouseRelease();
}

void ACBCameraController::CameraZoomController(float Direction)
{
	if (Direction == 0 || SpringArmComponent == nullptr) return;
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Direction * ZoomSpeed,
	                                                   MinZoom, MaxZoom);
}

void ACBCameraController::MoveForwardOrBackward(float Direction)
{
	if (MyCameraCharachter == nullptr) return;
	float SpeedFactor = FMath::Clamp(SpringArmComponent->TargetArmLength / MaxZoom, 1.0f, 20.0f);
	MyCameraCharachter->AddMovementInput(MyCameraCharachter->GetActorForwardVector(), Direction * SpeedFactor, false);
}

void ACBCameraController::MoveLeftOrRight(float Direction)
{
	if (MyCameraCharachter == nullptr) return;

	float SpeedFactor = FMath::Clamp(SpringArmComponent->TargetArmLength / MaxZoom, 1.0f, 20.0f);
	MyCameraCharachter->AddMovementInput(MyCameraCharachter->GetActorRightVector(), Direction * SpeedFactor, false);
}

void ACBCameraController::LookLeftOrRight(float Direction)
{
	if (bIsRightMouseClicked == false || Direction == 0 || MyCameraCharachter == nullptr) return;
	MyCameraCharachter->AddControllerYawInput(Direction * LookingRotationSpeed);
}

void ACBCameraController::LookUpOrDown(float Direction)
{
	if (bIsRightMouseClicked == false || Direction == 0 || SpringArmComponent == nullptr) return;
	FRotator DeltaRotation;
	DeltaRotation.Pitch = Direction * LookingRotationSpeed;
	DeltaRotation.Roll = 0;
	DeltaRotation.Yaw = 0;
	SpringArmComponent->AddLocalRotation(DeltaRotation, false, nullptr);

	float TargetPitch = FMath::Clamp(SpringArmComponent->GetRelativeRotation().Pitch, MinPitch, MaxPitch);

	FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
	NewRotation.Pitch = TargetPitch;
	SpringArmComponent->SetRelativeRotation(NewRotation);
}

void ACBCameraController::RotateBuilding(float Direction)
{
	if (Direction == 0 || MyCameraCharachter == nullptr)return;;
	MyCameraCharachter->RotateBuilding(Direction, BuildingRotationSpeed);
}

void ACBCameraController::SellBuilding()
{
	if (MyCameraCharachter == nullptr) return;
	MyCameraCharachter->SellBuilding();
}

void ACBCameraController::ToggleSnap()
{
	MyCameraCharachter->ToggleSnap();
}

void ACBCameraController::ToggleInfo()
{
	//TODO: event mesh sh8al lesa 
	OnToggleMenuInfo.Broadcast();
	MyCameraCharachter->ToggleInfoMenu();
}

void ACBCameraController::DisableBuildingContainer()
{
	//TODO: event mesh sh8al lesa 
	if (IsMouseOverUI()) return;
	
	UCBUIControllerComponent* UcbuiControllerComponent = Cast<UCBUIControllerComponent>(
		GetCharacter()->GetComponentByClass(UCBUIControllerComponent::StaticClass()));
	UcbuiControllerComponent->DisableBuildingsContainer();
}

bool ACBCameraController::IsMouseOverUI()
{
	// Get the viewport that you want to access the UI widgets for.
	UCBUIControllerComponent* UcbuiControllerComponent = Cast<UCBUIControllerComponent>(
		GetCharacter()->GetComponentByClass(UCBUIControllerComponent::StaticClass()));
	
	if(UcbuiControllerComponent->MainHud->BuildingContainerBorder->IsHovered()) return true;

	return  false;
}
