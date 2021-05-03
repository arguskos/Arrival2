// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShape.h"
#include "UObject/NoExportTypes.h"
#include "Circle.generated.h"

/**
 *
 */

UCLASS()
class ASTEROID_API UCircle : public UBaseShape
{
	GENERATED_BODY()
public:                  
	void Init(float radius, AActor* connectedActor);
	float GetRadius() const { return Radius; }
	virtual bool Intersect( UBaseShape* other) const;
	virtual bool IntersectWith(const UBaseShape* circle) const;
	virtual bool IntersectWith(const UCircle* circle) const;
	virtual bool IntersectWith(const URectangle* circle) const;

private:
	float Radius;
};

