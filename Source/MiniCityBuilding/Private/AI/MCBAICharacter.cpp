// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MCBAICharacter.h"

// Sets default values
AMCBAICharacter::AMCBAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMCBAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMCBAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

