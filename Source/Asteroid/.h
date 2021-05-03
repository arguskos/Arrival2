#pragma once
#include "CoreMinimal.h"
#include "Weapons/BaseBullet.h"
#include "BaseAsteroid.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewAsteroid, ABaseAsteroid*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewBullet, ABaseBullet*, Actor);
