#include "AbilitySystem/Abilities/Enemy/HitReactAbility.h"

void UHitReactAbility::CacheHitDirectionVectors(AActor* Instigator)
{
    AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();

    const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
    const FVector InstigatorLocation = Instigator->GetActorLocation();

    ToInstigator = InstigatorLocation - AvatarLocation;
    ToInstigator.Normalize();
}
