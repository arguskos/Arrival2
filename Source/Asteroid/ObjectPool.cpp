// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"
#include "PoolableActor.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();
	Init(PreSpawn);
}

// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPool::Init(int32 preSpawn) {
	PreSpawn = preSpawn;
	//and people say I have bad naimings...
	Actors.SetNum(PreSpawn);
	for (int i = 0; i < PreSpawn; i++) {
		APoolableActor* spawnedActor = (APoolableActor*)GetWorld()->SpawnActor(PooledObjectSubclass);
		spawnedActor->SetActive(false);
		Actors[i] = spawnedActor;
		if (OnNewObjectSpawned.IsBound()) {
			OnNewObjectSpawned.Broadcast(spawnedActor);
		}
	}
}
 
APoolableActor* UObjectPool::GetActor() {
	for (APoolableActor* actor : Actors) {
		if (!actor->IsActive()) {
			actor->SetActive(true);
			return actor;
		}
	}
	APoolableActor* spawnedActor = (APoolableActor*)GetWorld()->SpawnActor(PooledObjectSubclass);
	if (OnNewObjectSpawned.IsBound()) {
		OnNewObjectSpawned.Broadcast(spawnedActor);
	}
	Actors.Add(spawnedActor);
	return spawnedActor;
}

void UObjectPool::FreeActor(APoolableActor* actor) {
	actor->SetActive(true);
}
