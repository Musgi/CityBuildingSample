// Fill out your copyright notice in the Description page of Project Settings.


#include "CBBaseBuilding.h"

#include "CBBuildingBaseState.h"
#include "States/CBBuildingState_Colliding.h"
#include "States/CBBuildingState_Idle.h"
#include "States/CBBuildingState_Preview.h"
#include "States/CBBuildingState_Selected.h"
// Sets default values

ACBBaseBuilding::ACBBaseBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	StateManager = CreateDefaultSubobject<USMStateManagerComponent>("State Manager");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh Component");
	RedColor = FVector(1, 0, 0);
	GreenColor = FVector(0, 1, 0);
	WhiteColor = FVector(1, 1, 1);
}


void ACBBaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	SetOriginalMaterial();
}

void ACBBaseBuilding::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckForOverlap();
}

void ACBBaseBuilding::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (StaticMeshComponent == nullptr)
		return

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ACBBaseBuilding::OnBuildingBeginOverlap);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ACBBaseBuilding::OnBuildingEndOverlap);
}

void ACBBaseBuilding::OnBuildingBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	if (OtherActor == this) return;
	//if (ObjectState == Idle || ObjectState == Fade)
	if (StateManager->CurrentState->IsA(UCBBuildingState_Idle::StaticClass()))
	{
		//UpdateState(Fade);
		return;
	}
	ChangeBuildingState("Colliding");
}

void ACBBaseBuilding::OnBuildingEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this) return;
	if (StateManager->CurrentState->IsA(UCBBuildingState_Idle::StaticClass()))
	{
		return;
	}
	ChangeBuildingState("Selected");
}

void ACBBaseBuilding::CheckForOverlap()
{
	if (CanCheckForOverlap() == false) return;

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, StaticClass());

	if (OverlappingActors.Num() == 0)
	{
		ChangeBuildingState("Selected");
		return;
	}
	ChangeBuildingState("Colliding");
}

bool ACBBaseBuilding::CanCheckForOverlap()
{
	return StateManager->CurrentState->IsA(UCBBuildingState_Preview::StaticClass()) ||
		StateManager->CurrentState->IsA(UCBBuildingState_Selected::StaticClass()) ||
		StateManager->CurrentState->IsA(UCBBuildingState_Colliding::StaticClass());
}

FVector ACBBaseBuilding::ColorToVector(FColor Color)
{
	return FVector((float)Color.R / 255.0f, (float)Color.G / 255.0f, (float)Color.B / 255.0f);
}

void ACBBaseBuilding::SetOriginalMaterial()
{
	if (bOriginalMaterialsIsSet == true) return;

	OriginalMaterials = StaticMeshComponent->GetMaterials();
	if (OriginalMaterials.Num() > 0)
		bOriginalMaterialsIsSet = true;
}

void ACBBaseBuilding::SetTempMaterial()
{
	TempMaterialsForChangingStates = StaticMeshComponent->GetMaterials();
	bRestoreFromTempMaterials = true;
}


void ACBBaseBuilding::FadeObject(bool FadeOrNoFAde)
{
	if (FadeMaterial == nullptr) return;

	if (FadeOrNoFAde == true)
	{
		int32 i = 0;
		for (UMaterialInterface* Material : OriginalMaterials)
		{
			StaticMeshComponent->SetMaterial(i++, FadeMaterial);
			//FVector NewColor = ColorToVector(Green);
			StaticMeshComponent->SetVectorParameterValueOnMaterials("Color", GreenColor);
		}
	}
	else
	{
		ResetMaterials();
	}
}

void ACBBaseBuilding::ResetMaterials()
{
	int32 i = 0;
	TArray<UMaterialInterface*> TargetMaterials;
	if (bRestoreFromTempMaterials == true)
	{
		TargetMaterials = TempMaterialsForChangingStates;
		bRestoreFromTempMaterials = false;
	}
	else
	{
		TargetMaterials = OriginalMaterials;
	}

	for (UMaterialInterface* Material : TargetMaterials)
	{
		StaticMeshComponent->SetMaterial(i++, Material);
	}
}

void ACBBaseBuilding::ApplyCollisionVisual(bool Colliding)
{
	if (Colliding == true)
		SetTempMaterial();
	for (UMaterialInterface* Material : TempMaterialsForChangingStates)
	{
		if (Colliding == true)
		{
			//FVector NewColor = ColorToVector(Red);
			StaticMeshComponent->SetVectorParameterValueOnMaterials("Color", RedColor);
		}
		else
		{
			if (bStillInPreview == true)
			{
				//FVector NewColor = ColorToVector(Green);
				StaticMeshComponent->SetVectorParameterValueOnMaterials("Color", GreenColor);
			}
			else
			{
				//FVector NewColor = ColorToVector(White);
				StaticMeshComponent->SetVectorParameterValueOnMaterials("Color", WhiteColor);
			}
		}
	}
}

void ACBBaseBuilding::ApplyHoverVisual(bool Hovered)
{
	FVector NewColor = ColorToVector(White);
	if (Hovered == true)
	{
		//NewColor = ColorToVector(Hover);
		StaticMeshComponent->SetVectorParameterValueOnMaterials("Color", NewColor);
	}
	else
		StaticMeshComponent->SetVectorParameterValueOnMaterials("Color", NewColor);
}

void ACBBaseBuilding::SetInPreviewState(bool StillInPreview)
{
	bStillInPreview = StillInPreview;
}


void ACBBaseBuilding::ChangeBuildingState(FString NewState)
{
	if (NewState == "Hovered" && StateManager->CurrentState->IsA(UCBBuildingState_Selected::StaticClass())) return;
	StateManager->SwitchStateByKey(NewState);
}

USMStateBase* ACBBaseBuilding::GetCurrentBuildingState()
{
	return StateManager->CurrentState;
}

void ACBBaseBuilding::SetOutlineState(bool bOutlineOn)
{
	StaticMeshComponent->SetRenderCustomDepth(bOutlineOn);
}

bool ACBBaseBuilding::IsColliding()
{
	return StateManager->CurrentState->IsA(UCBBuildingState_Colliding::StaticClass());
}
