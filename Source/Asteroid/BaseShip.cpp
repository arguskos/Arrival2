// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShip.h"
#include "Camera/CameraComponent.h"
#include "AsteroidGameModeBase.h"
#include "Weapons/BaseGun.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseShip::ABaseShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    // Create a camera and a visible object
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
    // Attach our camera and visible object to our root component. Offset and rotate the camera.
    //OurCamera->SetupAttachment(RootComponent);
    OurVisibleComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABaseShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseShip::Tick(float DeltaTime)
{

}

// Called to bind functionality to input
void ABaseShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ABaseShip::Action);
	PlayerInputComponent->BindAxis("MoveX", this, &ABaseShip::Move);
	PlayerInputComponent->BindAxis("MoveY", this, &ABaseShip::Rotate);
}

void ABaseShip::Init(class FNewBullet* newBulletSpawned) {
    NewBulletSpawned = newBulletSpawned;
	TArray<UBaseGun*> weapons;
	GetComponents<UBaseGun>(weapons);
    for (auto& weapon : weapons) {
        Cast<UBaseGun>(weapon)->Init(NewBulletSpawned);
    }
}

void ABaseShip::Action() {
	if (OnAction.IsBound())
	{
		OnAction.Broadcast();
	}
}