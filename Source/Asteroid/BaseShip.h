// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "BaseShip.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionDelegate);
class UCollisionChecker;
class UObjectWrapper;
UCLASS(ABSTRACT)
class ASTEROID_API ABaseShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Init(class FNewBullet* newBulletSpawned);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool isDead) { IsDead = isDead; }
	UFUNCTION(BlueprintCallable)
	bool GetIsDead() const { return IsDead; }
protected:
	virtual void Move(float value) PURE_VIRTUAL(ABaseShip::Move, );
	virtual void Rotate(float value) PURE_VIRTUAL(ABaseShip::Rotate, );
	virtual void Action();

public:
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	FActionDelegate OnAction;
	FNewBullet* NewBulletSpawned;
protected:
	bool IsDead;
};