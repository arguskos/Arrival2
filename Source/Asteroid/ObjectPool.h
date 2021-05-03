// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewObjectSpawned, APoolableActor*, Actor);

class APoolableActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROID_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPool();
	APoolableActor* GetActor();
	void FreeActor(APoolableActor* actor);
	template<typename T>
	void SetSpawnType(TSubclassOf<T> actor) {
		PooledObjectSubclass = actor;
	}
	void Init(int32 PreSpawn);
	const TArray<APoolableActor*>& GetAllActors() const { return Actors; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FNewObjectSpawned OnNewObjectSpawned;

private:
	UPROPERTY(EditDefaultsOnly, Category = "ObjectPool")
	int32 PreSpawn;
	UPROPERTY(EditAnywhere, Category = "ObjectPool")
    TSubclassOf<APoolableActor> PooledObjectSubclass;

	TArray<APoolableActor*> Actors;

};
