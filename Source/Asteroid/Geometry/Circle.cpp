// Fill out your copyright notice in the Description page of Project Settings.


#include "Circle.h"
#include "Rectangle.h"

void UCircle::Init(float radius, AActor* connectedActor) {
	Radius = radius;
	ConnectedActor = connectedActor;
}

bool UCircle::Intersect( UBaseShape* other) const {
	ensure(ConnectedActor);
	return false;
}

bool UCircle::IntersectWith(const UBaseShape* other) const {
	//return other->IntersectWith(this);
	return other->IntersectWith(this);
}

bool UCircle::IntersectWith(const UCircle* circle) const {
	FVector distanceVector = ConnectedActor->GetActorLocation() - circle->GetConnectedActor()->GetActorLocation();
	float distance = distanceVector.Size2D();
	bool intersects = distance <= Radius + circle->Radius;
	return intersects;
}
bool UCircle::IntersectWith(const URectangle* rectangle) const {
	return true;
}