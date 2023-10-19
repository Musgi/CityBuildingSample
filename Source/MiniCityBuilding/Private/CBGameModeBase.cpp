// Fill out your copyright notice in the Description page of Project Settings.


#include "CBGameModeBase.h"
#include "CBCameraCharachter.h"
#include "Kismet/GameplayStatics.h"

void ACBGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ListenToBuildingEvents();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("AISpawner"), FoundActors);
	if (FoundActors.Num() > 0)
		AISpawaner = Cast<AMCBAISpawner>(FoundActors[0]);
	// UE::Kismet::tag
}

void ACBGameModeBase::ClearDebugDrawing()
{
	DrawDebugSphere(GetWorld(), MidPointBetweenBuldings, 0, 32, FColor::Red, false, 3);
}

void ACBGameModeBase::GetMidPointBetweenBuildings()
{
	if(ActiveBuildings.IsEmpty()) return;
	FVector3d TempLocation = FVector3d::Zero();
	
	for (const AActor* Building : ActiveBuildings)
	{
		TempLocation += Building->GetActorLocation();
	}
	
	TempLocation /= ActiveBuildings.Num();
	MidPointBetweenBuldings = TempLocation;

	DrawDebugSphere(GetWorld(), MidPointBetweenBuldings, 50, 32, FColor::Red, false, 3);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,MidPointBetweenBuldings.ToString(), true);
	OnDestinationMidPointChanged.Broadcast(MidPointBetweenBuldings);
	
}

void ACBGameModeBase::ListenToBuildingEvents()
{
	// APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// APawn* Pawn = PlayerController->GetPawn();
	// ACBCameraCharachter* MyCharacter = Cast<ACBCameraCharachter>(Pawn);

	ACBCameraCharachter* MyCharacter = Cast<ACBCameraCharachter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	MyCharacter->OnBuildingCreated.AddDynamic(this, &ACBGameModeBase::AddNewBuilding);
	MyCharacter->OnBuildingDestroyed.AddDynamic(this, &ACBGameModeBase::RemvoeBuilding);
	MyCharacter->OnBuildingLocationChanged.AddDynamic(this, &ACBGameModeBase::RecalculateMidPoint);
}

void ACBGameModeBase::AddNewBuilding(AActor* NewBuilding)
{
	ActiveBuildings.Add(NewBuilding);
	//recalculate mid and broadcast it
	//ClearDebugDrawing();
	GetMidPointBetweenBuildings();
}

void ACBGameModeBase::RemvoeBuilding(AActor* OldBuilding)
{
	ActiveBuildings.Remove(OldBuilding);
	//recalculate mid and broadcast it
	//ClearDebugDrawing();
	GetMidPointBetweenBuildings();
}

void ACBGameModeBase::RecalculateMidPoint(AActor* MovedBuilding)
{
	//ClearDebugDrawing();
	GetMidPointBetweenBuildings();
}

void ACBGameModeBase::SetActorInactivePool(AActor* Actor)
{
	check(AISpawaner);
	AISpawaner->SetActorInactive(Actor);
}
