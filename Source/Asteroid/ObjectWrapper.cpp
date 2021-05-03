// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectWrapper.h"
#include "UnrealClient.h"

void UObjectWrapper::Init(const FVector2D& size) {
	Size = size / 2; 
	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &UObjectWrapper::OnResize);
}

void UObjectWrapper::Tick(float deltaTime)
{
	for (AActor* actor : WrapActors) {
		if (actor->IsValidLowLevel()) {

			FVector location = actor->GetActorLocation();
			if (location.X < -Size.X) {
				location.X = Size.X;
				Wrap(actor, location);
			}
			else if (location.X > Size.X) {
				location.X = -Size.X;
				Wrap(actor, location);
			}
			else if (location.Y < -Size.Y) {
				location.Y = Size.Y;
				Wrap(actor, location);
			}
			else if (location.Y > Size.Y) {
				location.Y = -Size.Y;
				Wrap(actor, location);
			}
		}

	}
}

void UObjectWrapper::AddToWrap(AActor* actor)
{
	WrapActors.Add(actor);
}

void UObjectWrapper::RemoveFromWrap(AActor* actor)
{
	WrapActors.RemoveSingle(actor);
}

void UObjectWrapper::Wrap(AActor* actor, const FVector& newLocation)
{
	actor->SetActorLocation(newLocation);
}

void UObjectWrapper::OnResize(FViewport* ViewPort, uint32 val) {
	Size.Y = ViewPort->GetSizeXY().X/2;
	Size.X = ViewPort->GetSizeXY().Y/2;
}
