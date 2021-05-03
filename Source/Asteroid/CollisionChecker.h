// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include "UObject/NoExportTypes.h"
#include "CollisionChecker.generated.h"

/**
 * 
 */
class UBaseShape;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollisionDelegate, AActor*, Actor, AActor*, Other);

struct CollisionInfo {
	CollisionInfo(int32 layer, int32 mask, UBaseShape* shape, FCollisionDelegate onCollision) :
		Layer(layer), Mask(mask), Shape(shape), Collision(onCollision)
{

}
int32 Layer;
int32 Mask;
UBaseShape* Shape;
FCollisionDelegate Collision;
};

UCLASS()
class ASTEROID_API UCollisionChecker : public UObject
{
	GENERATED_BODY()
	
public:
	void RegisterActor(int32 layer, int32 mask, AActor* actor, UBaseShape* shape, FCollisionDelegate callabck);
	void UnRegisterActor(AActor* actor);
	void Tick(float DeltaTime);
private:
	TArray<TPair<AActor*, CollisionInfo>> RegisteredActors;
};
