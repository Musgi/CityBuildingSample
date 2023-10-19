// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SMStateBase.h"
#include "SMStateManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CUSTOMSTATEMACHINE_API USMStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USMStateManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="State Machine")
	FString InitialState;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="State Machine")
	TMap<FString, TSubclassOf<USMStateBase>> AvailableStates;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="State Machine Debug")
	bool bCanDebug;

	UPROPERTY(BlueprintReadOnly)
	TArray<USMStateBase*> StateHistory;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="State Machine")
	int32 StateHistoryLength;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USMStateBase* CurrentState;
	UPROPERTY()
	TMap<FString,USMStateBase*> StateMap;

	
	
	UFUNCTION(BlueprintCallable)
	void SwitchStateByKey(FString Key);

	private:
	bool bCanTickState;
	void InitilaizeStates();
};
