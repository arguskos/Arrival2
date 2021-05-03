// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShape.h"

//bool UBaseShape::Intersect(UBaseShape* other) {
//
//	return false;
//}

void UBaseShape::Init(AActor* actor) {
	ensure(actor);
	ConnectedActor = actor;
}