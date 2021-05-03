// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PhysicsState.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API UPhysicsState : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FVector& velocity, const FVector& acceleration);
	FVector GetVelocity() const;
	FVector GetAccelearation() const;
	
	void SetVelocity(FVector velocity);
	void SetAcceleration(FVector acceleration);
	float GetSpeed() const;
	
private:
	FVector Velocity{};
	FVector Acceleration{};

};
