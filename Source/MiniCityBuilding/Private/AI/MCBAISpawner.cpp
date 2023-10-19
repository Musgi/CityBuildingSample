// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MCBAISpawner.h"

#include "CBGameModeBase.h"
#include "AI/MCBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/Core/Analytics/NetStatsUtils.h"

// Sets default values
AMCBAISpawner::AMCBAISpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMCBAISpawner::BeginPlay()
{
	Super::BeginPlay();
	CreateCharachterPool();
}

// Called every frame
void AMCBAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACBGameModeBase* GameModeBase = Cast<ACBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(GameModeBase);
	if (GameModeBase->ActiveBuildings.IsEmpty()) return;
	TimeTicks += DeltaTime;
	if (TimeTicks >= IntervalBetweenSpawns)
	{
		SpawnAICharachter();
		TimeTicks = 0;
	}
	
}

void AMCBAISpawner::SpawnAICharachter()
{
	if (AICharachters.IsEmpty()) return;
	if (AICharachterPool.IsEmpty()) return;

	SetActorActive(AICharachterPool[0]);
	AICharachterPool.RemoveAtSwap(0);
}

void AMCBAISpawner::CreateCharachterPool()
{
	AICharachterPool.Reserve(NumberOfAICharachtersToSpawn);

	for (int i = 0; i < NumberOfAICharachtersToSpawn; i++)
	{
		if (AICharachters.IsEmpty()) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AICharachterActor, GetActorLocation(),
		                                                      FRotator::ZeroRotator,
		                                                      SpawnParams);
		SetActorInactive(SpawnedActor);
	}
}

void AMCBAISpawner::SetActorInactive(AActor* Actor)
{
	// Activate the actor
	Actor->SetActorHiddenInGame(true);
	//SpawnedActor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);
	Actor->GetComponentByClass(UCharacterMovementComponent::StaticClass())->Deactivate();
	Actor->SetActorLocation(GetActorLocation());
	AICharachterPool.AddUnique(Actor);
}

void AMCBAISpawner::SetActorActive(AActor* Actor)
{
	int32 RandomInteger = FMath::RandRange(0, AICharachters.Num() - 1);
	USkeletalMeshComponent* ActorSkeleMesh = Cast<USkeletalMeshComponent>(
		Actor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	ActorSkeleMesh->SetSkeletalMesh(AICharachters[RandomInteger]->CharachterMesh);

	Actor->SetActorHiddenInGame(false);
	//SpawnedActor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(true);
	Actor->GetComponentByClass(UCharacterMovementComponent::StaticClass())->Activate();

	AMCBAIController* Aic = Cast<AMCBAIController>(Cast<AMCBAICharacter>(Actor)->GetController());
	UBlackboardComponent* bBc = Aic->GetBlackboardComponent();
	FVector currentloc = bBc->GetValueAsVector("CurrentDestination");

	DrawDebugSphere(GetWorld(), currentloc, 60, 32, FColor::Green, false, 3);
}
