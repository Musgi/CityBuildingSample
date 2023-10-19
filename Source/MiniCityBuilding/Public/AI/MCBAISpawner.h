// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCBAICharachterDataAsset.h"
#include "MCBAICharacter.h"
#include "GameFramework/Actor.h"
#include "MCBAISpawner.generated.h"

UCLASS()
class MINICITYBUILDING_API AMCBAISpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMCBAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetActorInactive(AActor* Actor);

private:
	UPROPERTY(EditDefaultsOnly, Category= "Spawner")
	TSubclassOf<AMCBAICharacter> AICharachterActor;
	UPROPERTY(EditAnywhere, Category= "Spawner")
	TArray<TObjectPtr<UMCBAICharachterDataAsset>> AICharachters;
	UPROPERTY(EditAnywhere, Category= "Spawner")
	float IntervalBetweenSpawns = 1.0;
	UPROPERTY(EditAnywhere, Category= "Spawner")
	int NumberOfAICharachtersToSpawn = 10;

	float TimeTicks = 0;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AActor>> AICharachterPool;

	void SpawnAICharachter();
	void CreateCharachterPool();
	void SetActorActive(AActor* Actor);

};
