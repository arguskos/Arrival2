// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAsteroid.h"
#include "AsteroidManager.generated.h"
/**
 * 
 */

class FNewAsteroid;
UCLASS(Blueprintable)
class ASTEROID_API UAsteroidManager : public  UObject
{
	GENERATED_BODY()	
public:
	UAsteroidManager();
	void BeginPlay();
	void Tick(float DeltaTime);
	void Init(FVector2D screenSize, const FNewAsteroid* onNewAsteroid);
	const TArray<ABaseAsteroid*>& GetAsteroids() const;
	void Hit(ABaseAsteroid* asteroid);
	int32 GetIteration() const { return Iteration; }
private:
	void SpawnAsteroid(float scale);
	void SpawnAsteroid(const FVector &location, const FVector &velocity, float scale);

	UFUNCTION() 
	void AsteriodSpawned(APoolableActor* actor);
	void NewIteration();
private:
	UPROPERTY(EditAnywhere)
	float MinSpawnDistance;
	UPROPERTY(EditAnywhere)
	float MaxSpawnDistance;


	UPROPERTY(EditAnywhere)
	float MinAsteroidVelocity;
	UPROPERTY(EditAnywhere)
	float MaxAsteroidVelocity;

	UPROPERTY(EditAnywhere)
	float MinScale = 0.2;
	UPROPERTY(EditAnywhere)
	int32 BreakPieces = 2;
	
	UPROPERTY(EditAnywhere)
	FBox2D WorldBoundaries;


	UPROPERTY(EditAnywhere)
	int32 StartAsteroids;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseAsteroid> Asteroid;
private:
	class UObjectPool* AsteroidPool;

	TArray<ABaseAsteroid*> Asteroids;
	TArray<ABaseAsteroid*> Transitioning;
	
	FVector2D ScreenSize;
	const FNewAsteroid* OnNewAsteroid;
	int32 Iteration = 0;

};
