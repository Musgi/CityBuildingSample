// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCityBuilding/Public/States/CBBuildingState_Preview.h"

#include "CBBaseBuilding.h"

UCBBuildingState_Preview::UCBBuildingState_Preview()
{
	bCanTick = false;
	bCanRepeat = false;
	StateName = "Preview";
}

void UCBBuildingState_Preview::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);

	if(StateOwnerActor == nullptr) return;

	StateOwnerActor->SetOriginalMaterial();
	StateOwnerActor->FadeObject(true);
}

void UCBBuildingState_Preview::TickState()
{
	Super::TickState();
	
}

void UCBBuildingState_Preview::OnExitState(AActor* StateOwner)
{
	Super::OnExitState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);

	if(StateOwnerActor == nullptr) return;
	//StateOwnerActor->FadeObject(false);
	//StateOwnerActor->ResetMaterials();
}
