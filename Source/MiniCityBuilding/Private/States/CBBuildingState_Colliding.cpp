// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCityBuilding/Public/States/CBBuildingState_Colliding.h"

#include "CBBaseBuilding.h"

UCBBuildingState_Colliding::UCBBuildingState_Colliding()
{
	bCanRepeat = false;
	bCanTick = false;
	StateName = "Colliding";
}

void UCBBuildingState_Colliding::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);

	if(StateOwnerActor == nullptr) return;

	//StateOwnerActor->SetOriginalMaterial();
	StateOwnerActor->ApplyCollisionVisual(true);
}

void UCBBuildingState_Colliding::TickState()
{
	Super::TickState();
}

void UCBBuildingState_Colliding::OnExitState(AActor* StateOwner)
{
	Super::OnExitState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);

	if(StateOwnerActor == nullptr) return;

	StateOwnerActor->ApplyCollisionVisual(false);
	StateOwnerActor->ResetMaterials();
}
