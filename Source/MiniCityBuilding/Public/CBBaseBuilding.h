// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBBuildingDataAsset.h"
#include "GameFramework/Actor.h"
#include "SMStateManagerComponent.h"
#include "CBBaseBuilding.generated.h"

UCLASS()
class MINICITYBUILDING_API ACBBaseBuilding : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACBBaseBuilding();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	UCBBuildingDataAsset* BuildingData;

	void ChangeBuildingState(FString NewState);
	USMStateBase* GetCurrentBuildingState();
	void SetOutlineState(bool bOutlineOn);
	bool IsColliding();
	void SetOriginalMaterial();
	void SetTempMaterial();
	void FadeObject(bool FadeOrNoFAde);
	void ResetMaterials();
	void ApplyCollisionVisual(bool Colliding);
	void ApplyHoverVisual(bool Hovered);
	void SetInPreviewState(bool StillInPreview);

protected:
	UPROPERTY(EditDefaultsOnly)
	USMStateManagerComponent* StateManager;
	UPROPERTY()
	TArray<UMaterialInterface*> OriginalMaterials;
	UPROPERTY()
	TArray<UMaterialInterface*> TempMaterialsForChangingStates;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* FadeMaterial;
	UPROPERTY(EditDefaultsOnly)
	FColor Red;
	UPROPERTY(EditDefaultsOnly)
	FColor Green;
	UPROPERTY(EditDefaultsOnly)
	FColor Blue;
	UPROPERTY(EditDefaultsOnly)
	FColor Hover;
	UPROPERTY(EditDefaultsOnly)
	FColor White;
	bool bStillInPreview = true;
	bool bIsOverlapping = false;
	bool bOriginalMaterialsIsSet = false;
	bool bRestoreFromTempMaterials = false;
	FVector RedColor;
	FVector WhiteColor;
	FVector GreenColor;

	UFUNCTION()
	void OnBuildingBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBuildingEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                          int32 OtherBodyIndex);

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void CheckForOverlap();
	bool CanCheckForOverlap();
	FVector ColorToVector(FColor Color);
};
