// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINICITYBUILDING_API UCBInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCBInteractionComponent();

	UFUNCTION()
	AActor* DoLineTraceForActor(FVector StartLocation, FVector Direction,float LineLength);
	FVector DoLineTraceForGround(FVector StartLocation, FVector Direction,float LineLength);
protected:
	// Called when the game starts
public:	

	// Called every frame

		
};
