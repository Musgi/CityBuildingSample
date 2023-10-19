// Fill out your copyright notice in the Description page of Project Settings.


#include "CBBuildingButton.h"


void UCBBuildingButton::InializeButton(UCBBuildingDataAsset* BuildingDataInitialize)
{
	BuildingData = BuildingDataInitialize;
	Icon->SetBrushFromTexture(BuildingData->BuildingIcon);
	Button->OnClicked.AddDynamic(this,&UCBBuildingButton::OnButtonClicked);
	Button->OnHovered.AddDynamic(this,&UCBBuildingButton::OnButtonHovered);
	Button->OnUnhovered.AddDynamic(this,&UCBBuildingButton::OnButtonUnhovered);
}

void UCBBuildingButton::OnButtonClicked()
{
	MyButtonClicked.Broadcast(BuildingData);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Clicked: " + BuildingData->BuildingName.ToString());
}

void UCBBuildingButton::OnButtonHovered()
{
	MyButtonHovered.Broadcast(BuildingData->Cost,BuildingData->BuildingName);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Hovered: " + BuildingData->BuildingName.ToString());
}

void UCBBuildingButton::OnButtonUnhovered()
{
	MyButtonUnHovered.Broadcast();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, "Unhovered: " + BuildingData->BuildingName.ToString());
}

