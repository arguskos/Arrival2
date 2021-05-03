// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsState.h"

void UPhysicsState::Init(const FVector& velocity, const FVector& acceleration)
{
	Velocity = velocity;
	Acceleration = acceleration;
}

FVector UPhysicsState::GetVelocity() const {
	return Velocity;
}

FVector UPhysicsState::GetAccelearation() const {
	return Acceleration;
}

void UPhysicsState::SetVelocity(FVector velocity) {
	Velocity = velocity;
}

void UPhysicsState::SetAcceleration(FVector acceleration) {
	Acceleration = acceleration;
}

float UPhysicsState::GetSpeed() const {
	return Velocity.Size();
}