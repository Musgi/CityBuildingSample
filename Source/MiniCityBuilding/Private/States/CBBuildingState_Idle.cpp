// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCityBuilding/Public/States/CBBuildingState_Idle.h"
#include "CBBaseBuilding.h"

UCBBuildingState_Idle::UCBBuildingState_Idle()
{
	bCanTick = false;
	bCanRepeat = false;
	StateName = "Idle";
}

void UCBBuildingState_Idle::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);
	StateOwnerActor->SetOutlineState(false);
	// StateOwnerActor->ApplyHoverVisual(false);
	StateOwnerActor->FadeObject(false);
	StateOwnerActor->ResetMaterials();
}
