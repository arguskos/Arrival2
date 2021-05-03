// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidGameModeBase.generated.h"

/**
 * 
 */

class ABaseAsteroid;
class ABaseBullet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewAsteroid, ABaseAsteroid*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewBullet, ABaseBullet*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsteroidDestroyed, ABaseAsteroid*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreUpdated, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLivesUpdated, int32, Lives);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShipDestroyed);

class UAsteroidManager;
UCLASS()
class ASTEROID_API AAsteroidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAsteroidGameModeBase();
	void StartPlay() override;
	UFUNCTION(BlueprintCallable)
	UAsteroidManager* GetAsteroidSpawner() const;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SetScore(int32 newScore);
	UFUNCTION(BlueprintCallable)
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable)
	int32 GetLives() const;

private:
	UFUNCTION()
	void OnNewAsteroid(ABaseAsteroid* actor);
	UFUNCTION()
	void OnNewBullet(ABaseBullet* actor);
	UFUNCTION()
	void OnCollision(AActor* actor, AActor* other);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UAsteroidManager> Manager;
	UPROPERTY(EditDefaultsOnly)
	int32 Lives = 3;
	UAsteroidManager* AsteroidSpawner;
	class UObjectWrapper* ObjectWrapper;
	class ABaseShip* PlayerShip;
	class UCollisionChecker* CollisionChecker;
	int32 Score;
	TArray<ABaseAsteroid*> HitAsteroids;

	FNewAsteroid NewAsteroidSpawned;
	FNewBullet NewBulletSpawned;
	UPROPERTY(BlueprintAssignable)
	FAsteroidDestroyed AsteroidDestroyed;
	UPROPERTY(BlueprintAssignable)
	FScoreUpdated ScoreUpdated;
	UPROPERTY(BlueprintAssignable)
	FLivesUpdated LivesUpdated;

	UPROPERTY(BlueprintAssignable)
	FShipDestroyed ShipDestroyed;
};
