// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableActor.h"

// Sets default values
APoolableActor::APoolableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoolableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableActor::SetActive(bool state) {
	SetActorHiddenInGame(!state);
	SetActorTickEnabled(state);
	Active = state;
}

bool APoolableActor::IsActive() const {
	return Active;
}

