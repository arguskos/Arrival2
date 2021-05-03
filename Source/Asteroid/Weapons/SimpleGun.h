// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGun.h"
#include "BaseBullet.h"
#include "SimpleGun.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class ASTEROID_API USimpleGun : public UBaseGun
{
	GENERATED_BODY()


public:
	USimpleGun();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init(const FNewBullet* onNewBullet) override;
	void Fire_Implementation() override;
	bool IsReady_Implementation() override;
protected:
	void BeginPlay() override;
private:
	UFUNCTION()
	void OnNewBulletSpawned(APoolableActor* actor);

public:

private:
	UPROPERTY(EditDefaultsOnly)
	float ReloadTime = 1;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseBullet> BulletType;
	float CurrentReloading;
	class UObjectPool* BulletPool;
	bool IsReady = true;
};
