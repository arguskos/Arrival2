// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShape.generated.h"

/**
 * 
 */
class UCircle;
class URectangle;

UCLASS(Abstract)
class ASTEROID_API UBaseShape : public UObject
{
	GENERATED_BODY()
public:
	void Init(AActor* actor);
	virtual bool Intersect( UBaseShape* other) const { return false; }
	virtual bool IntersectWith(const UBaseShape* circle) const { return false; }
	virtual bool IntersectWith(const UCircle* circle) const { return false; }
	virtual bool IntersectWith(const URectangle* circle) const { return false; }
	AActor* GetConnectedActor() const { return ConnectedActor; }
protected:
	AActor* ConnectedActor;
};
