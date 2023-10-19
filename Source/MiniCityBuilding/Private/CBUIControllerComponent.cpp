// Fill out your copyright notice in the Description page of Project Settings.


#include "CBUIControllerComponent.h"

#include "CBCameraCharachter.h"
#include "CBMainHud.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

// Sets default values for this component's properties
UCBUIControllerComponent::UCBUIControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (UCBBuildingDataAsset* Data : BuildingData)
	{
		//if (Data != nullptr)
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "t");
	}
}


// Called when the game starts
void UCBUIControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	MyCharachter = Cast<ACBCameraCharachter>(GetOwner());

	if (MainHudClass == nullptr) return;
	MainHud = CreateWidget<UCBMainHud>(GetWorld(), MainHudClass);
	if (MainHud == nullptr) return;
	MainHud->AddToViewport();

	if (MyMoneyClass != nullptr)
	{
		MyMoney = CreateWidget<UUserWidget>(GetWorld(), MyMoneyClass);
		if (MyMoney != nullptr)
			MyMoney->AddToViewport();
	}
	MainHud->BuildingInfoContainer->SetVisibility(ESlateVisibility::Hidden);
	//MainHud->SelectedBuildingToSpawn.AddDynamic(this, &UCBUIControllerComponent::SetBuildingToBuild);
	// for (UCBBuildingDataAsset* Data : BuildingData)
	for (int32 i = 0; i < BuildingData.Num(); i++)
	{
		UCBBuildingDataAsset* Data = BuildingData[i];
		UCBBuildingButton* NewBuildingButton = CreateWidget<UCBBuildingButton>(
			GetWorld(), BuildingButtonClass);
		//NewBuildingButton->set
		NewBuildingButton->InializeButton(Data);
		ListenToButtonEvents(NewBuildingButton);
		UHorizontalBoxSlot* ButtonSlot = MainHud->BuildingButtonContainer->AddChildToHorizontalBox(NewBuildingButton);
		MainHud->BuildingContainerBorder->SetVisibility(ESlateVisibility::Collapsed);
		if (ButtonSlot != nullptr)
		{
			ButtonSlot->SetSize(ESlateSizeRule::Automatic);
			ButtonSlot->SetVerticalAlignment(VAlign_Center);
			ButtonSlot->SetHorizontalAlignment(HAlign_Center); // Auto-fit
		}
	}
	MainHud->BuildingMenuToggle->OnClicked.AddDynamic(this,&UCBUIControllerComponent::EnableBuildingsContainer);
//	MainHud->FakeBorderButton->DisableEvents();
}



void UCBUIControllerComponent::UpdateMoneyUI(int CurrentMoney)
{
	UTextBlock* TextBlock = Cast<UTextBlock>(MyMoney->GetWidgetFromName("MoneyValue"));
	if (TextBlock != nullptr)
	{
		TextBlock->SetText(FText::AsNumber(CurrentMoney));
	}
}

void UCBUIControllerComponent::ListenToButtonEvents(UCBBuildingButton* FuncBuildingButton)
{
	FuncBuildingButton->MyButtonClicked.AddDynamic(this, &UCBUIControllerComponent::ButtonClicked);
	FuncBuildingButton->MyButtonHovered.AddDynamic(this, &UCBUIControllerComponent::ButtonHovered);
	FuncBuildingButton->MyButtonUnHovered.AddDynamic(this, &UCBUIControllerComponent::ButtonUnHovered);
}

void UCBUIControllerComponent::ToggleInputInfo()
{
	ESlateVisibility Visibility = ESlateVisibility::Hidden;
	
	if (MainHud->InputControlInfoContainer->Visibility == ESlateVisibility::Hidden)
		Visibility = ESlateVisibility::Visible;

	MainHud->InputControlInfoContainer->SetVisibility(Visibility);
}

void UCBUIControllerComponent::ButtonClicked(UCBBuildingDataAsset* FuncBuildingData)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Clicked: ");
	if (MyCharachter == nullptr) return;
	MyCharachter->SpawnBuilding(FuncBuildingData);
}

void UCBUIControllerComponent::ButtonHovered(int Cost, FName Name)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Hovered: ");
	FString PriceText = FString::Printf(TEXT("Cost : %d"), Cost);
	//FString Name = FString::Printf(TEXT("This is an example with an integer: %d"), MyIntValue);
	MainHud->BuildingCost->SetText(FText::FromString(PriceText));
	FString Info = Name.ToString();
	MainHud->BuildingInfo->SetText(FText::FromString(Info));
	MainHud->BuildingInfoContainer->SetVisibility(ESlateVisibility::Visible);
}

void UCBUIControllerComponent::ButtonUnHovered()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "UnHovered: ");
	MainHud->BuildingInfoContainer->SetVisibility(ESlateVisibility::Hidden);
}

void UCBUIControllerComponent::EnableBuildingsContainer()
{
	MainHud->BuildingContainerBorder->SetVisibility(ESlateVisibility::Visible);
	MainHud->BuildingMenuToggle->SetVisibility(ESlateVisibility::Collapsed);
}

void UCBUIControllerComponent::DisableBuildingsContainer()
{
	if(MainHud->BuildingContainerBorder->IsHovered()) return;
	MainHud->BuildingContainerBorder->SetVisibility(ESlateVisibility::Collapsed);
	MainHud->BuildingMenuToggle->SetVisibility(ESlateVisibility::Visible);
}
