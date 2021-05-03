// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBullet.h"
#include "GameFramework/Actor.h"
#include "SimpleBullet.generated.h"

UCLASS()
class ASTEROID_API ASimpleBullet : public ABaseBullet
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(const FVector& location, const FVector& direction) override;
private:
	UPROPERTY(EditAnywhere)
	float Speed = 5;
	UPROPERTY(EditAnywhere)
	float BulletDisappearRange = 500;
	float TravelDistance = 0;

};
