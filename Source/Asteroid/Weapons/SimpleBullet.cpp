// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleBullet.h"

// Sets default values
ASimpleBullet::ASimpleBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector velocity = Direction * Speed * DeltaTime;
	SetActorLocation(GetActorLocation() + velocity);
	TravelDistance += Speed * DeltaTime;
	if (TravelDistance >= BulletDisappearRange) {
		SetActive(false);
	}
}

void ASimpleBullet::Init(const FVector& location, const FVector& direction) {
	Super::Init(location, direction);
	TravelDistance = 0;
}