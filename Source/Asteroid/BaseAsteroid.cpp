// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAsteroid.h"
#include "PhysicsState.h"

// Sets default values
ABaseAsteroid::ABaseAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PhysicsState = NewObject<UPhysicsState>();
}

// Called when the game starts or when spawned
void ABaseAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector position = GetActorLocation();
	FVector veclocity = PhysicsState->GetVelocity();
	SetActorLocation(position + veclocity * DeltaTime);

}

void ABaseAsteroid::Init(const FVector& position, const FVector& velocity) {
	SetActorLocation(position);
	PhysicsState = NewObject<UPhysicsState>();
	PhysicsState->Init(velocity, FVector(0));
}

UPhysicsState* ABaseAsteroid::GetPhysics() const {
	return PhysicsState;
}
