// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MCBAIController.h"

#include "CBGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AMCBAIController::AMCBAIController()
{
	
}

void AMCBAIController::BeginPlay()
{
	Super::BeginPlay();
	check(MainBhevaiourTree);
	RunBehaviorTree(MainBhevaiourTree);
	ACBGameModeBase* GameModeBase = CastChecked<ACBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeBase->OnDestinationMidPointChanged.AddDynamic(this, &AMCBAIController::UpdateBlackBoardDestinationValue);
	GetBlackboardComponent()->SetValueAsVector("CurrentDestination", FVector3d::Zero());
}

void AMCBAIController::UpdateBlackBoardDestinationValue(FVector3d NewLocation)
{
	GetBlackboardComponent()->SetValueAsVector("NewDestination", NewLocation);
}
