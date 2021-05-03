// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

void ABaseBullet::Init(const FVector& location, const FVector& direction) {
	SetActorLocation(location);
	Direction = direction;
}