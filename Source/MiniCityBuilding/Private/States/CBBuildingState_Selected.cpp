// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCityBuilding/Public/States/CBBuildingState_Selected.h"

#include "CBBaseBuilding.h"

UCBBuildingState_Selected::UCBBuildingState_Selected()
{
	bCanTick = false;
	bCanRepeat= false;
	StateName = "Selected";
}

void UCBBuildingState_Selected::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);

	if(StateOwnerActor == nullptr) return;

	StateOwnerActor->SetOutlineState(true);
}

void UCBBuildingState_Selected::TickState()
{
	Super::TickState();
}

void UCBBuildingState_Selected::OnExitState(AActor* StateOwner)
{
	Super::OnExitState(StateOwner);
}
