// Fill out your copyright notice in the Description page of Project Settings.
//TODO: Left click sets selected and stays selected untill clicked elsewhere  hovering still highlights change whole logic of selection

#include "CBInteractionComponent.h"

#include "CBBaseBuilding.h"

// Sets default values for this component's properties
UCBInteractionComponent::UCBInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UCBInteractionComponent::DoLineTraceForActor(FVector StartLocation, FVector Direction, float LineLength)
{
	// FRotator CameraRotation = CameraTransform.GetRotation().Rotator();
	FVector LineTraceEndLocation = StartLocation + Direction * LineLength;
	//FVector MouseLocation;
	FCollisionObjectQueryParams ObjectQueryParam;
	ObjectQueryParam.AddObjectTypesToQuery(ECC_WorldStatic);

	FHitResult Hit;

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, StartLocation, LineTraceEndLocation,
	                                                            ObjectQueryParam);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	AActor* HitActor = Hit.GetActor();

	//DrawDebugLine(GetWorld(), StartLocation, LineTraceEndLocation, LineColor, false, .05f, 0, 0);

	//FString CombinedString = FString::Printf(TEXT("Hit Location %s"), *Hit.ImpactPoint.ToString());
	if (HitActor)
	{
		if (Cast<ACBBaseBuilding>(HitActor) != nullptr)
		{
			//DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, .05, true);
			return HitActor;
		}
	}
	//CombinedString = FString::Printf(TEXT("Hit Location %s"), *LineTraceEndLocation.ToString());
	//DrawDebugString(GetWorld(), LineTraceEndLocation, CombinedString, nullptr, FColor::Red, .05, true);

	return nullptr;
}

FVector UCBInteractionComponent::DoLineTraceForGround(FVector StartLocation, FVector Direction, float LineLength)
{
	// FRotator CameraRotation = CameraTransform.GetRotation().Rotator();
	FVector LineTraceEndLocation = StartLocation + Direction * LineLength;
	//FVector MouseLocation;
	FCollisionObjectQueryParams ObjectQueryParam;
	ObjectQueryParam.AddObjectTypesToQuery(ECC_GameTraceChannel1);
	
	ECollisionChannel CollisionChannel = ECC_GameTraceChannel1;
	TArray<FHitResult> Hits;
	
	bool bBlockingHit = GetWorld()->LineTraceMultiByChannel(Hits, StartLocation, LineTraceEndLocation,
	                                                        CollisionChannel);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	if (bBlockingHit == false) return FVector::Zero();
	AActor* HitActor = Hits[0].GetActor();

	//DrawDebugLine(GetWorld(), StartLocation, LineTraceEndLocation, LineColor, false, .05f, 0, 0);

	FString CombinedString = FString::Printf(TEXT("Hit Location %s"), *Hits[0].ImpactPoint.ToString());
	if (HitActor)
	{
		//if (Cast<ACBBaseBuilding>(HitActor) != nullptr)
		{
			//DrawDebugString(GetWorld(), Hits[0].ImpactPoint, CombinedString, nullptr, FColor::Green, .05, true);
			return Hits[0].Location;
		}
	}
	//CombinedString = FString::Printf(TEXT("Hit Location %s"), *LineTraceEndLocation.ToString());
	//DrawDebugString(GetWorld(), LineTraceEndLocation, CombinedString, nullptr, FColor::Red, .05, true);

	return FVector::Zero();
}
