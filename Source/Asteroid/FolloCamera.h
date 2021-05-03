// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "FolloCamera.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API AFolloCamera : public AActor
{
	GENERATED_BODY()
public:
	AFolloCamera();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	float FollowTime = 1;

private:
	UCameraComponent* Camera;
};
