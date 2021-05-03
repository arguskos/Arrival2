// Fill out your copyright notice in the Description page of Project Settings.


#include "FolloCamera.h"
#include "Camera/CameraComponent.h"

AFolloCamera::AFolloCamera() {
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
}

void AFolloCamera::BeginPlay() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT("Camera begin play"));
}

void AFolloCamera::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT("Camera test"));
}
