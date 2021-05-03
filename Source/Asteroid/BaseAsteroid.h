// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.h"
#include "BaseAsteroid.generated.h"

UCLASS()
class ASTEROID_API ABaseAsteroid : public APoolableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAsteroid();
	void Init(const FVector& position, const FVector& velocity);
	class UPhysicsState* GetPhysics() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/*UPROPERTY(EditAnywhere)
	float MinStartVelocity;
	UPROPERTY(EditAnywhere)
	float MaxStartVelocity;*/
	class UPhysicsState* PhysicsState;
};
