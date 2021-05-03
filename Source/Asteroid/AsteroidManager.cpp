// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidManager.h"
#include "ObjectPool.h"
#include "BaseAsteroid.h"
#include "PhysicsState.h"
#include "AsteroidGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

UAsteroidManager::UAsteroidManager()
{
	AsteroidPool = CreateDefaultSubobject<UObjectPool>(TEXT("ASteroidPool "));
}

void UAsteroidManager::BeginPlay() {

}

void UAsteroidManager::Tick(float DeltaTime) {
	
}

void UAsteroidManager::Init(FVector2D screenSize, const FNewAsteroid* onNewAsteroid) {
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ScreenSize = FVector2D(ViewportSize.Y, ViewportSize.X);
	DrawDebugBox(GetWorld(), FVector(0), FVector(ScreenSize, 20), FQuat::Identity, FColor(1, 0, 0), true);
	OnNewAsteroid = onNewAsteroid;

	AsteroidPool->OnNewObjectSpawned.AddDynamic(this, &UAsteroidManager::AsteriodSpawned);
	AsteroidPool->SetSpawnType<ABaseAsteroid>(Asteroid);
	AsteroidPool->Init(StartAsteroids * StartAsteroids);
	for (int i = 0; i < StartAsteroids; i++) {
		SpawnAsteroid(2);
	}
}


void UAsteroidManager::Hit(ABaseAsteroid* asteroid) {
	if (asteroid->GetActorScale().X / 2 >= MinScale) {
		for (int i = 0; i < BreakPieces; i++) {
			FVector velocity = asteroid->GetPhysics()->GetVelocity();
			float angle1 = FMath::RandRange(0, 360);
			velocity = velocity.RotateAngleAxis(FMath::RandRange(0, 180), FVector(0, 0, 1));
 			velocity *= FMath::RandRange(1, 2.0);
			velocity = velocity.GetClampedToSize(MinAsteroidVelocity, MaxAsteroidVelocity);
			SpawnAsteroid(asteroid->GetActorLocation(), velocity, asteroid->GetActorScale().X / 2);
		}
	}
	asteroid->SetActive(false);
	for (auto& asteroid1 : Asteroids) {
		if (asteroid1->IsActive()) {
			return;
		}
	}
	NewIteration();
}

const TArray<ABaseAsteroid*>& UAsteroidManager::GetAsteroids() const {
	return Asteroids;
}

void UAsteroidManager::SpawnAsteroid(float scale) {
	float distance = FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);
	float angle = FMath::RandRange(0, 360);
	FVector vector = FVector(distance, 0, 0).RotateAngleAxis(angle, FVector(0, 0, 1));

	float distance1 = FMath::RandRange(MinAsteroidVelocity, MaxAsteroidVelocity / 2);
	float angle1 = FMath::RandRange(0, 360);
	FVector velocity = FVector(distance1, 0, 0).RotateAngleAxis(angle1, FVector(0, 0, 1));
	SpawnAsteroid(vector, velocity, scale);
}

void UAsteroidManager::SpawnAsteroid(const FVector& location, const FVector& velocity, float scale) {
	ABaseAsteroid* asteroid = Cast<ABaseAsteroid>(AsteroidPool->GetActor());
	asteroid->SetActorScale3D(FVector(scale, scale, scale));
	asteroid->Init(location, velocity);
	Asteroids.Add(asteroid);
}

void UAsteroidManager::AsteriodSpawned(APoolableActor* actor) {
	if (OnNewAsteroid->IsBound()) {
		OnNewAsteroid->Broadcast(Cast<ABaseAsteroid>(actor));
	}
}

void UAsteroidManager::NewIteration() {
	Iteration++;
	for (int i = 0; i < StartAsteroids + Iteration; i++) {
		SpawnAsteroid(2);
	}
}

