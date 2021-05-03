// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionChecker.h"
#include "Geometry/BaseShape.h"
#include <algorithm>

void UCollisionChecker::RegisterActor(int32 layer, int32 mask, AActor* actor, UBaseShape* shape, FCollisionDelegate callback) {
	auto it = Algo::FindByPredicate(RegisteredActors, [actor](const auto& other)
		{
			if (other.Get<0>() == actor) {
				return true;
			}
			return false;
		});
	if (!it) {
		RegisteredActors.Add(TPair<AActor*, CollisionInfo>(actor, CollisionInfo(layer, mask, shape, callback)));
	}
}

void UCollisionChecker::UnRegisterActor(AActor* actor) {

	RegisteredActors.RemoveAll([actor](const auto& other) {
		if (other.Get<0>() == actor) {
			return true;
		}
		return false;
	});
}

void UCollisionChecker::Tick(float DeltaTime) {
	for (const auto& actorAndInfo : RegisteredActors) {
		for (const auto& otherAndInfo : RegisteredActors) {
			const CollisionInfo& actorsInfo = actorAndInfo.Get<1>();
			const CollisionInfo& othersInfo = otherAndInfo.Get<1>();
			AActor* actor = actorAndInfo.Get<0>();
			AActor* other = otherAndInfo.Get<0>();
			bool isOtherLayerInMask = (actorsInfo.Mask) & (1 << othersInfo.Layer);
			if (
				actor && other &&
				actor->IsValidLowLevel() && other->IsValidLowLevel() &&
				actor->IsActorTickEnabled() &&
				other->IsActorTickEnabled() &&
				//actor != other &&
 				isOtherLayerInMask &&
				actorsInfo.Shape->IntersectWith(othersInfo.Shape)
				 ) {
		
				if (actorsInfo.Collision.IsBound()) {
					actorsInfo.Collision.Broadcast(actor, other);
				}
				if (othersInfo.Collision.IsBound()) {
					othersInfo.Collision.Broadcast(other, actor);
				}
			}
		}
	}
}
