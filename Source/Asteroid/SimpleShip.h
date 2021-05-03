// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "SimpleShip.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API ASimpleShip : public ABaseShip
{
	GENERATED_BODY()
public:
	ASimpleShip();
	virtual void Tick(float DeltaTime) override;

private:
	void Move(float delta) override;
	void Rotate(float delta) override;
	void Action() override;
public:
	UPROPERTY(EditAnywhere)
	float Acceleration = 1;
	UPROPERTY(EditAnywhere)
	float Rotation = 1;
	UPROPERTY(EditAnywhere)
	float MaxVelocity;
private:
	float Throttle;
	float Steer;
	class UPhysicsState* PhysicsState;

};
