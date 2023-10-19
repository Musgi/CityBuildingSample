// Fill out your copyright notice in the Description page of Project Settings.


#include "SMStateBase.h"

void USMStateBase::OnEnterState(AActor* StateOwner)
{
	if(StateOwner == nullptr)return;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		//								 "Entering  " + StateName.ToString() + " State From " + StateOwner->GetName(), true);
}

void USMStateBase::TickState()
{
	
}

void USMStateBase::OnExitState(AActor* StateOwner)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
									//	 "Exiting  " + StateName.ToString() + " State", true);

}
