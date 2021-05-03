// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShip.h"
#include "Math/UnrealMathUtility.h" 
#include "PhysicsState.h"

ASimpleShip::ASimpleShip() : Super() {
	PhysicsState = NewObject<UPhysicsState>();
}

void ASimpleShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector pos = GetActorLocation();
	auto acceleration = GetActorForwardVector() * Throttle * Acceleration * DeltaTime;
	PhysicsState->SetAcceleration(acceleration);

	FVector velocity = PhysicsState->GetVelocity();

	velocity += acceleration;
	velocity *= 0.99f;
	velocity = velocity.GetClampedToSize(-MaxVelocity, MaxVelocity);
	PhysicsState->SetVelocity(velocity);
	SetActorLocation(pos + velocity );

	FRotator NewRotation = FRotator(0, Steer * Rotation  * DeltaTime, 0);
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ASimpleShip::Move(float delta) {
	Throttle = delta;
}

void ASimpleShip::Rotate(float delta) {

	Steer = delta;

}

void ASimpleShip::Action() {
	Super::Action();
}
