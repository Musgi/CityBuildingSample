// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CBBTService_CheckLocation.h"

#include "AIController.h"
#include "CBGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void UCBBTService_CheckLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	ensure(Blackboard);
	FVector3d CurrentDestination = Blackboard->GetValueAsVector("CurrentDestination");
	FVector3d NewDestination = Blackboard->GetValueAsVector("NewDestination");
	if (CurrentDestination == NewDestination)
	{
		Blackboard->SetValueAsBool("LocationChanged", false);
	}
	else
	{
		Blackboard->SetValueAsBool("LocationChanged", true);
		Blackboard->SetValueAsVector("CurrentDestination",NewDestination);
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	check(AIController);
	APawn * AIPawn = AIController->GetPawn();
	check(AIPawn);
	
	ACBGameModeBase * GameModeBase = Cast<ACBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(GameModeBase);
	
	if(FVector3d::Distance(CurrentDestination,AIPawn->GetActorLocation()) < 100)
		GameModeBase->SetActorInactivePool(AIPawn);
	//todo Use the object pooling in spawner (link it to gamemodebase then fetch the spawner from there)
		
}
