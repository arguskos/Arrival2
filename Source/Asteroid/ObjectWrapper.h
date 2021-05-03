// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealClient.h"
#include "ObjectWrapper.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_API UObjectWrapper : public UObject
{
	GENERATED_BODY()
public:
	void Init(const FVector2D &size);
	void Tick(float deltaTime);
	void AddToWrap(AActor* actor);
	void RemoveFromWrap(AActor* actor);
	void OnResize(FViewport* ViewPort, uint32 val);
private:
	void Wrap(AActor* actor, const FVector& newLocation);
private:
	FVector2D Size;
	//You could use set but iteration will be slower and it's the most common operation so using array
	TArray<AActor*> WrapActors;
};
