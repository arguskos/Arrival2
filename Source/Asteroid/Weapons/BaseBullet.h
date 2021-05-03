// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PoolableActor.h"
#include "BaseBullet.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API ABaseBullet : public APoolableActor
{
	GENERATED_BODY()
public:
	virtual void Init(const FVector& location, const FVector& direction);


protected:
	FVector Direction;
};
