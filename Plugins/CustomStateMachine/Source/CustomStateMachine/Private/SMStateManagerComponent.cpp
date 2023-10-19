// Fill out your copyright notice in the Description page of Project Settings.


#include "SMStateManagerComponent.h"

// Sets default values for this component's properties
USMStateManagerComponent::USMStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USMStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	InitilaizeStates();
	// ...
}

void USMStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bCanTickState == true)
	{
		CurrentState->TickState();
	}
	if (bCanDebug)
	{
		if (CurrentState)
			//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green,
			                  //               this->GetOwner()->GetName() + "'s current state: " + CurrentState->
			                  //               StateName.GetPlainNameString());
		if (StateHistory.Num() > 0)
		{
			for (int32 i = 0; i < StateHistory.Num(); i++)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple,
				                          //       this->GetOwner()->GetName() + "'s past state" +
				                        //         FString::FromInt(i) + "" + StateHistory[i]->GetName());
			}
		}
	}
}

void USMStateManagerComponent::SwitchStateByKey(FString Key)
{
	USMStateBase* NewState = StateMap.FindRef(Key);
	if (NewState->IsValidLowLevel())
	{
		if (CurrentState == nullptr)
		{
			CurrentState = NewState;
		}
		else
		{
			if (CurrentState->GetClass() == NewState->GetClass())
			{
				if (CurrentState->bCanRepeat == false)
				{
					if (bCanDebug)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
						                          //       this->GetOwner()->GetName() +
						                         //        "'s State switch Failed. "
						                         //        + CurrentState->StateName.GetPlainNameString() +
						                          //       " Is not repeatable"
						                          //       , true);
					}
				}
				return;
			}
			
			bCanTickState = false;
			CurrentState->OnExitState(GetOwner());
			if (StateHistory.Num() >= StateHistoryLength)
			{
				StateHistory.RemoveAt(0);
			}
			StateHistory.Push(CurrentState);
			CurrentState = NewState;
		}
		
		if (CurrentState)
		{
			CurrentState->OnEnterState(GetOwner());
			bCanTickState = true;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
		                                 this->GetOwner()->GetName() +
		                                 "'s State switch Failed. "
		                                 + "Invalid State."
		                                 , true);
	}
}

void USMStateManagerComponent::InitilaizeStates()
{
	for (auto It = AvailableStates.CreateConstIterator(); It; ++It)
	{
		USMStateBase* State = NewObject<USMStateBase>(this, It->Value);
		StateMap.Add(It->Key, State);
	}
}
