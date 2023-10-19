// Fill out your copyright notice in the Description page of Project Settings.


#include "CBCameraCharachter.h"
#include "CBBaseBuilding.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACBCameraCharachter::ACBCameraCharachter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm Component");
	InteractionComponent = CreateDefaultSubobject<UCBInteractionComponent>("Interaction Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UIManager = CreateDefaultSubobject<UCBUIControllerComponent>("UI Manager");
	SpringArmComponent->SetupAttachment(RootComponent);
	bIsLeftMouseClicked = false;
	CurrentGameState = Observing;
}


void ACBCameraCharachter::BeginPlay()
{
	Super::BeginPlay();
	//FRotator DefaultRotation = FRotator(0, -30, 0);
	//SetActorRotation(DefaultRotation);
	CurrentMoney = 1000;
	UpdateMoney();
}

void ACBCameraCharachter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentGameState == Spawning && SpawningActor != nullptr)
		DragActor(SpawningActor);
	else if (bIsLeftMouseClicked == true && SelectedActor != nullptr)
		DragActor(SelectedActor);
	else
		HoveringnBuilding();

	SnappingCoolDown -= DeltaSeconds;
}


bool ACBCameraCharachter::SpawnBuilding(UCBBuildingDataAsset* BuildingData)
{
	if (CurrentGameState == Spawning)
	{
		if (SpawningActor != nullptr)
			SpawningActor->Destroy();
	}
	else
		CurrentGameState = Spawning;
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, "Spawn Building ");

	if (BuildingData->Cost > CurrentMoney)
	{
		CurrentGameState = Observing;
		return false;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawningActor = GetWorld()->SpawnActor<AActor>(SpawnableBuilding, FVector::Zero(), FRotator::ZeroRotator,
	                                               SpawnParams);
	ACBBaseBuilding* NewBuilding = Cast<ACBBaseBuilding>(SpawningActor);
	NewBuilding->BuildingData = BuildingData;
	if (NewBuilding == nullptr) return false;

	NewBuilding->StaticMeshComponent->SetStaticMesh(BuildingData->StaticMesh);
	NewBuilding->StaticMeshComponent->SetCollisionObjectType(ECC_WorldStatic);
	NewBuilding->StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	NewBuilding->StaticMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	CurrentSpawningBuildingCost = BuildingData->Cost;
	NewBuilding->ChangeBuildingState("Preview");
	MouseDragOffset = FVector::Zero();
	return true;
}

void ACBCameraCharachter::ToggleSnap()
{
	bSnappingActive = !bSnappingActive;
}

void ACBCameraCharachter::ToggleInfoMenu()
{
	UIManager->ToggleInputInfo();
}

void ACBCameraCharachter::AddMoney(int Value)
{
	CurrentMoney += Value;
	UpdateMoney();
}

void ACBCameraCharachter::BuildingCreated()
{
	OnBuildingCreated.Broadcast(SpawningActor);
}

void ACBCameraCharachter::BuildingDestroyed()
{
	OnBuildingDestroyed.Broadcast(SelectedActor);
}

void ACBCameraCharachter::BuildingMoved()
{
	OnBuildingLocationChanged.Broadcast(SelectedActor);
}


void ACBCameraCharachter::DragActor(AActor* TargetActor)
{
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(
		MouseWorldLocation, MouseWorldDirection);
	FVector NewLocation = InteractionComponent->DoLineTraceForGround(
		MouseWorldLocation, MouseWorldDirection, SpringArmComponent->TargetArmLength * 10.0f);
	NewLocation.Z = 50.0f;
	FVector FinalLocation = NewLocation - MouseDragOffset;
	if (bSnappingActive == false)
	{
		TargetActor->SetActorLocation(FinalLocation);
	}
	else
	{
		FVector SnappedNewLocation = RoundToNearestGridCellLocation(FinalLocation);
		TargetActor->SetActorLocation(SnappedNewLocation);
		FRotator SnappingRotation = RoundYAWToNearest90XRotation(TargetActor->GetActorRotation());
		TargetActor->SetActorRotation(SnappingRotation);
	}
}

AActor* ACBCameraCharachter::LineTraceForBuildingSelectingAndOutline()
{
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(
		MouseWorldLocation, MouseWorldDirection);

	return InteractionComponent->DoLineTraceForActor(MouseWorldLocation, MouseWorldDirection,
	                                                 SpringArmComponent->TargetArmLength * 10.0f);
}

void ACBCameraCharachter::UpdateMoney()
{
	UIManager->UpdateMoneyUI(CurrentMoney);
}

bool ACBCameraCharachter::UpdateBuildingState(FString NewState, AActor* TargetActor)
{
	if (TargetActor == nullptr) return false;
	ACBBaseBuilding* TargetBuilding = Cast<ACBBaseBuilding>(TargetActor);
	if (TargetBuilding == nullptr) return false;
	TargetBuilding->ChangeBuildingState(NewState);
	return true;
}

void ACBCameraCharachter::HoveringnBuilding()
{
	AActor* NewHoveredActor = LineTraceForBuildingSelectingAndOutline();
	if (NewHoveredActor == nullptr)
	{
		UpdateBuildingState("Idle", HoveredActor);
		HoveredActor = nullptr;
		return;
	}
	if(NewHoveredActor == SelectedActor) return;
	
	UpdateBuildingState("Idle", HoveredActor);
	UpdateBuildingState("Hovered", NewHoveredActor);
	HoveredActor = NewHoveredActor;
}


void ACBCameraCharachter::CalculateMouseDragOffset(AActor* TargetActor)
{
	SelectedActorOriginalTransform = TargetActor->GetTransform();
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(
		MouseWorldLocation, MouseWorldDirection);
	FVector NewLocation = InteractionComponent->DoLineTraceForGround(
		MouseWorldLocation, MouseWorldDirection, SpringArmComponent->TargetArmLength * 10.0f);
	MouseDragOffset = NewLocation - TargetActor->GetActorLocation();
	MouseDragOffset.Z = 0;
}

FVector ACBCameraCharachter::RoundToNearestGridCellLocation(FVector Location)
{
	int32 OriginalX = FMath::RoundToInt32(Location.X);
	int32 OriginalY = FMath::RoundToInt32(Location.Y);


	int32 RemainderX = OriginalX % SnappingGridCellSize;
	int32 RemainderY = OriginalY % SnappingGridCellSize;

	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "RemainderX : "
	//                                  + FString::FromInt(RemainderX)
	//                                  + "RemainderY : "
	//                                  + FString::FromInt(RemainderY), true, FVector2d(1.5, 1.5)
	// );
	OriginalX -= RemainderX;
	OriginalY -= RemainderY;
	if (RemainderX >= SnappingGridCellSize * 0.5f)
		OriginalX += SnappingGridCellSize;
	if (RemainderY >= SnappingGridCellSize * 0.5f)
		OriginalY += SnappingGridCellSize;

	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "FinalX : "
	//                                  + FString::FromInt(OriginalX)
	//                                  + "FinalY : "
	//                                  + FString::FromInt(OriginalY), true, FVector2d(1.5, 1.5)
	// );

	return FVector(OriginalX, OriginalY, Location.Z);
}

FRotator ACBCameraCharachter::RoundYAWToNearest90XRotation(FRotator Rotation)
{
	int32 OriginalYAW = FMath::RoundToInt32(Rotation.Yaw) + 180;
	//OriginalYAW = FMath::Abs(OriginalYAW);
	int32 RemainderYAW = OriginalYAW % 90;
	OriginalYAW -= RemainderYAW;
	//int32 YAWSign = FMath::Sign(OriginalYAW);
	if (RemainderYAW >= 45)
		OriginalYAW += 90;

	Rotation.Yaw = OriginalYAW - 180;

	return Rotation;
}


void ACBCameraCharachter::LeftMouseClick()
{
	//TODO : Fe 8aba2 fel code hena lazm ytsl7

	if (CurrentGameState == Spawning)
	{
		UpdateBuildingState("Idle", SelectedActor);
		SelectedActor = nullptr;

		if (SpawningActor != nullptr)
		{
			ACBBaseBuilding* TargetBuilding = Cast<ACBBaseBuilding>(SpawningActor);
			if (TargetBuilding == nullptr) return;
			if (TargetBuilding->IsColliding())
			{
				SpawningActor->Destroy();
				CurrentGameState = Observing;
				return;
			}
			ACBBaseBuilding* Building = Cast<ACBBaseBuilding>(SpawningActor);
			Building->SetInPreviewState(false);
			Building->ResetMaterials();
			CurrentMoney -= CurrentSpawningBuildingCost;
			CurrentSpawningBuildingCost = 0;
			UpdateMoney();
			UpdateBuildingState("Idle", SpawningActor);
			BuildingCreated();
			SpawningActor = nullptr;
			CurrentGameState = Observing;
		}
	}
	else
	{
		bIsLeftMouseClicked = true;
		AActor* NewActor = LineTraceForBuildingSelectingAndOutline();

		if (NewActor == nullptr)
		{
			UpdateBuildingState("Idle", SelectedActor);
			SelectedActor = nullptr;
			return;
		}

		if (SelectedActor == NewActor)
		{
			CalculateMouseDragOffset(SelectedActor);
			return;
		}

		//this changes the current selected 
		UpdateBuildingState("Idle", SelectedActor);
		UpdateBuildingState("Idle", HoveredActor);
		HoveredActor = nullptr;
		SelectedActor = NewActor;
		CalculateMouseDragOffset(SelectedActor);
		UpdateBuildingState("Selected", SelectedActor);
	}
}



void ACBCameraCharachter::LeftMouseRelease()
{
	if (SelectedActor == nullptr || bIsLeftMouseClicked == false) return;
	ACBBaseBuilding* TargetBuilding = Cast<ACBBaseBuilding>(SelectedActor);
	if (TargetBuilding->IsColliding())
	{
		SelectedActor->SetActorTransform(SelectedActorOriginalTransform);
	}
	BuildingMoved();
	//HoveredActor = SelectedActor;
	bIsLeftMouseClicked = false;
	//SelectedActor = nullptr;
}

void ACBCameraCharachter::RotateBuilding(float Direction, float RotationSpeed)
{
	if (Direction == 0 || (SelectedActor == nullptr && SpawningActor == nullptr) || (bIsLeftMouseClicked == false && CurrentGameState != Spawning)) return;
	if (bSnappingActive == true && SnappingCoolDown > 0) return;
	AActor* TargetActor;
	if (CurrentGameState == Spawning && SpawningActor != nullptr)
		TargetActor = SpawningActor;
	else
		TargetActor = SelectedActor;

	FRotator NewRotation = TargetActor->GetActorRotation();
	if (bSnappingActive == false)
		NewRotation.Yaw += Direction * RotationSpeed;
	else
	{
		NewRotation.Yaw += 90 * Direction;
		SnappingCoolDown = .1;
	}
	TargetActor->SetActorRotation(NewRotation);
}

void ACBCameraCharachter::SellBuilding()
{
	//TODO: Reset mouse money everything
	if (SelectedActor == nullptr) return;

	ACBBaseBuilding* TargetBuilding = Cast<ACBBaseBuilding>(SelectedActor);

	if (TargetBuilding == nullptr) return;
	CurrentMoney += TargetBuilding->BuildingData->Cost;
	UpdateMoney();
	MouseDragOffset = FVector::Zero();
	BuildingDestroyed();
	SelectedActor->Destroy();
	SelectedActor = nullptr;
}
