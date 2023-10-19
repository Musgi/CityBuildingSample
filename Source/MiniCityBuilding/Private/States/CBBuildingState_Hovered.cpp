// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniCityBuilding/Public/States/CBBuildingState_Hovered.h"
#include"CBBaseBuilding.h"


UCBBuildingState_Hovered::UCBBuildingState_Hovered()
{
	bCanTick = false;
	bCanRepeat= false;
	StateName = "Hovered";
}

void UCBBuildingState_Hovered::OnEnterState(AActor* StateOwner)
{
	Super::OnEnterState(StateOwner);
	ACBBaseBuilding* StateOwnerActor = Cast<ACBBaseBuilding>(StateOwner);

	if(StateOwnerActor == nullptr) return;

	StateOwnerActor->SetOutlineState(true);
}

void UCBBuildingState_Hovered::TickState()
{
	Super::TickState();
}

void UCBBuildingState_Hovered::OnExitState(AActor* StateOwner)
{
	Super::OnExitState(StateOwner);
}
