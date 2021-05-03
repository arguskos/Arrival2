// Fill out your copyright notice in the Description page of Project Settings.


#include "Rectangle.h"
#include "Circle.h"

//bool UBaseShape::Intersect(UBaseShape* other) {
//
//	return false;
//}

bool URectangle::Intersect( UBaseShape* other) const {
	ensure(ConnectedActor);
	return false;
}

bool URectangle::IntersectWith(const UBaseShape* other) const {
	return other->IntersectWith(this);
}

bool URectangle::IntersectWith(const UCircle* circle) const {
	return true;
}
bool URectangle::IntersectWith(const URectangle* circle) const {
	return false;
}