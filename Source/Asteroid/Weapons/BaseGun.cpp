// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGun.h"
#include "../BaseShip.h"
#include "../AsteroidGameModeBase.h"

// Sets default values for this component's properties
UBaseGun::UBaseGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBaseGun::BeginPlay()
{
	Super::BeginPlay();

	Ship = Cast<ABaseShip>(GetAttachmentRootActor());
	ensure(Ship);
	Ship->OnAction.AddDynamic(this, &UBaseGun::Fire);
}

// Called every frame
void UBaseGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UBaseGun::Init(const FNewBullet* newBullet) {
	NewBulletSpawned = newBullet;
}
