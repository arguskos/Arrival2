// Copyright Epic Games, Inc. All Rights Reserved.

#include "AsteroidGameModeBase.h"
#include "AsteroidManager.h"
#include "CollisionChecker.h"
#include "BaseShip.h"
#include "Weapons/BaseBullet.h"
#include "Geometry/BaseShape.h"
#include "Geometry/Circle.h"
#include "ObjectWrapper.h"

AAsteroidGameModeBase::AAsteroidGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroidGameModeBase::StartPlay() {
	Super::StartPlay();

	FVector2D Result = FVector2D(1, 1);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	CollisionChecker = NewObject<UCollisionChecker>(this);
	ObjectWrapper = NewObject<UObjectWrapper>(this);
	ObjectWrapper->Init(FVector2D(Result.Y, Result.X));

	if (Manager) {

		AsteroidSpawner = NewObject<UAsteroidManager>(this, Manager);
		AsteroidSpawner->BeginPlay();

		NewAsteroidSpawned.AddDynamic(this, &AAsteroidGameModeBase::OnNewAsteroid);
		AsteroidSpawner->Init(Result, &NewAsteroidSpawned);
	}

	PlayerShip = Cast<ABaseShip>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ensure(PlayerShip);
	NewBulletSpawned.AddDynamic(this, &AAsteroidGameModeBase::OnNewBullet);
	PlayerShip->Init(&NewBulletSpawned);
	ObjectWrapper->AddToWrap(PlayerShip);

	UCircle* playerCollision = NewObject<UCircle>(this);
	FVector center, extent;
	PlayerShip->GetActorBounds(false, center, extent);
	playerCollision->Init(extent.Y, PlayerShip);
	FCollisionDelegate Collison;
	Collison.AddDynamic(this, &AAsteroidGameModeBase::OnCollision);
	CollisionChecker->RegisterActor(4, 1, PlayerShip, playerCollision, Collison);

}

void AAsteroidGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (const auto& actor : HitAsteroids) {
		AsteroidSpawner->Hit(actor);
		if (AsteroidDestroyed.IsBound()) {
			AsteroidDestroyed.Broadcast(actor);
		}
	}
	HitAsteroids.Empty();

	if (AsteroidSpawner) {
		AsteroidSpawner->Tick(DeltaTime);
	}
	if (ObjectWrapper) {
		ObjectWrapper->Tick(DeltaTime);
	}
	if (CollisionChecker) {
		CollisionChecker->Tick(DeltaTime);
	}

}

UAsteroidManager* AAsteroidGameModeBase::GetAsteroidSpawner() const {
	return AsteroidSpawner;
}

void AAsteroidGameModeBase::OnNewAsteroid(ABaseAsteroid* asteroid) {
	ObjectWrapper->AddToWrap(asteroid);
	UCircle * asteroidCollision = NewObject<UCircle>(this);
	FVector center, extent;
	asteroid->GetActorBounds(false, center, extent);
	asteroidCollision->Init(FMath::Min(extent.X, extent.Y) - 50, asteroid);
	FCollisionDelegate Collison;
	Collison.AddDynamic(this, &AAsteroidGameModeBase::OnCollision);
	CollisionChecker->RegisterActor(0,  2, asteroid, asteroidCollision, Collison);
}

void AAsteroidGameModeBase::OnNewBullet(ABaseBullet* bullet) {
	ObjectWrapper->AddToWrap(bullet);
	UCircle* asteroidCollision = NewObject<UCircle>(this);
	FVector center, extent;
	bullet->GetActorBounds(false, center, extent);
	asteroidCollision->Init(50, bullet);
	FCollisionDelegate Collison;
	Collison.AddDynamic(this, &AAsteroidGameModeBase::OnCollision);
	CollisionChecker->RegisterActor(1, 1, bullet, asteroidCollision, Collison);
}

//This is not very clever but I am lazy
void AAsteroidGameModeBase::OnCollision(AActor* actor, AActor* other) {
	ABaseAsteroid* asteroid = Cast<ABaseAsteroid>(other);
	if (asteroid) {

		ABaseShip* ship = Cast<ABaseShip>(actor);
		if (ship && !ship->GetIsDead()) {
			Lives--;
			if (ShipDestroyed.IsBound()) {
				ShipDestroyed.Broadcast();
			}
			if (LivesUpdated.IsBound()) {
				LivesUpdated.Broadcast(Lives);
			}
			HitAsteroids.Add(asteroid);
			SetScore(GetScore() + 50 * (AsteroidSpawner->GetIteration() + 1));
			ship->SetIsDead(true);
		}
		else if (Cast<ABaseBullet>(actor)) {
			HitAsteroids.Add(asteroid);
			SetScore(GetScore() + 50 * (AsteroidSpawner->GetIteration() + 1));
		}
	}
	ABaseBullet* bullet = Cast<ABaseBullet>(other);
	if (bullet) {
		bullet->SetActive(false);
	}
}

void AAsteroidGameModeBase::SetScore(int32 newScore) {
	Score = newScore;
	if (ScoreUpdated.IsBound()) {
		ScoreUpdated.Broadcast(newScore);
	}
}

int32 AAsteroidGameModeBase::GetScore() const {
	return Score;
}

int32 AAsteroidGameModeBase::GetLives() const {
	return Lives	;
}