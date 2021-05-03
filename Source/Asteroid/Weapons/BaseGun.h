// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseGun.generated.h"

class FNewBullet;

UCLASS(ABSTRACT, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROID_API UBaseGun : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseGun();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void Init(const FNewBullet* onNewBullet);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();
	virtual void Fire_Implementation() {}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsReady();
	virtual bool IsReady_Implementation() { return false; }

protected:
	class ABaseShip* Ship;
	const FNewBullet* NewBulletSpawned;
};
