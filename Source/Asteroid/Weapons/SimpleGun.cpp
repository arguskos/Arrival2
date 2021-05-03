// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGun.h"
#include "../BaseShip.h"
#include "../ObjectPool.h"
#include "../AsteroidGameModeBase.h"

USimpleGun::USimpleGun() : Super(){
	BulletPool = CreateDefaultSubobject<UObjectPool>(TEXT("BulletPool "));

}

void USimpleGun::BeginPlay() {
	Super::BeginPlay();

	BulletPool->OnNewObjectSpawned.AddDynamic(this, &USimpleGun::OnNewBulletSpawned);
	BulletPool->SetSpawnType<APoolableActor>(BulletType);

}

void USimpleGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentReloading > 0) {
		CurrentReloading -= DeltaTime;
	}
	IsReady = CurrentReloading <= 0;
}

void USimpleGun::Init(const FNewBullet* onNewBullet) {
	Super::Init(onNewBullet);
	BulletPool->Init(1);
}


void USimpleGun::Fire_Implementation() {
	if (IsReady_Implementation()) {
 		ABaseBullet* bullet = Cast<ABaseBullet>(BulletPool->GetActor());
		bullet->Init(GetComponentLocation(), GetForwardVector());
		bullet->SetActorLocation(Ship->GetActorLocation());
		bullet->SetActorRotation(Ship->GetActorRotation());
		CurrentReloading = ReloadTime;
	}
}

bool USimpleGun::IsReady_Implementation() {
	return CurrentReloading <= 0;
}


void USimpleGun::OnNewBulletSpawned(APoolableActor* actor) {
	if (NewBulletSpawned && NewBulletSpawned->IsBound()) {
		NewBulletSpawned->Broadcast(Cast<ABaseBullet>(actor));
	}
}